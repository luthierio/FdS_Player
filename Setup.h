/**********************
* SETUP
***********************/
void setup() {
  /**********************
  * SERIAL:
  ***********************/
  Serial.begin(115200);
  if(SERIAL_ON){
    // Wait for serial port to be opened, remove this line for 'non debug'
    while (!Serial) { delay(1); }  
  }

  /**********************
  * DISPLAY:
  ***********************/    
  if(SCREEN_.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    DISPLAY_.init();
    setMode(LOGO);
    DEBUG_.print(F("✓✓✓ ⋅ Screen OK"));
  }
  /**********************
  * AUDIO:
  ***********************/
  if (! AUDIO.begin()) { // initialise the music player
    DISPLAY_.display.error(F("Pas de carte SON?"));
    DEBUG_.print(F("××× ⋅ Couldn't find VS1053, check PINS?"));
    while (1);
  }else{
    AUDIO.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
    DEBUG_.print(F("✓✓✓ ⋅ VS1053 found and started"));
    //Attention il faut désactiver Pitcher.init() pour faire le test... sinon ca buggue
    //AUDIO.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working
    //while (1);
    delay(500);
    PITCHER.init();
    // Set volume for left, right channels. lower numbers == louder volume!
    AUDIO.setVolume(VOLUME,VOLUME);
  }

  /**********************
  * FILES:
  ***********************/
  if (!SD.begin(CARDCS,SPI_SPEED)) {
    DISPLAY_.display.error(F("Pas de carte SD"));
    DEBUG_.print(F("××× ⋅ SD failed, or not present"));
    while (1);  // don't do anything more
  }else{
    DEBUG_.print(F("✓✓✓ ⋅ SD Card found "));
  }

  // Définir les callbacks
  SD_BACKUP.setCallbacks(onSDError, onBeforeSDReadWrite, onAfterSDReadWrite , onBeforeSDReadWrite, onAfterSDReadWrite );
  DEBUG_.print(F("✓✓✓ ⋅ FILES ok "));


  FILE_.setDirCallbacks( onBeforeSelectDir, onAfterSelectDir );
  FILE_.setFileCallbacks( onBeforeSelectFile, onAfterSelectFile );

  PLAYLISTS_.setCallbacks( onSetPosition );
  MARKERS_.setCallbacks( onMarkerAdd );

  SLEEP_WATCH.setCallbacks(onSleep, onWakeUp);
  SLEEP_WATCH.wakeUp();
  DEBUG_.print(F("✓✓✓ ⋅ Sleep Watch ok "));

  /**********************
  * INTERFACE: ROTARIES & BUTTONS  
  ***********************/

  for (byte i = 0; i < 3; ++i) {
    ROTARIES[i].begin(); // Remplacez 2 et 3 par les broches réelles de votre rotary encoder
    ROTARIES[i].setChangedHandler(onRotChange);
  }
  MUX.begin();
  BUTTONS.setCallbacks(onPress,onRelease,onLongPress,onLongRelease);
  DEBUG_.print(F("✓✓✓ ⋅ Interface ok "));
  DEBUG_.setSerial(SERIAL_ON); // A part les message d'entrée, on désactive le Serial
  
  // Play a file in the background, REQUIRES interrupts!  

  SD_BACKUP.load(MARKERS_FILENAME, &MARKERS, sizeof(MARKERS), true);  
  SD_BACKUP.load(PLAYLISTS_FILENAME, &PLAYLISTS, sizeof(PLAYLISTS), true);
  SD_BACKUP.load(STATE_FILENAME, &STATE, sizeof(STATE), true);

  FILE_.select(STATE.dirNum, STATE.fileNum); // Initialisation selon carte  
  PLAYLISTS_.setPosition( STATE.playlistPosition, true );  

  AUDIO.playFullFile(STARTSOUND);    

  setMode(STATE.MODE);
  
};