/**********************
* SETUP
***********************/
void setup() {
  /**********************
  * SERIAL:
  ***********************/
  if(SERIAL_ON){
    Serial.begin(115200);
    // Wait for serial port to be opened, remove this line for 'standalone' operation
    while (!Serial) { delay(1); }
  }
  /**********************
  * DISPLAY:
  ***********************/    
  if(SCREEN_.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    DISPLAY_.init();
    setMode(LOGO);
    Debug::print(F("✓✓✓ ⋅ Screen OK"));
  }
  /**********************
  * AUDIO:
  ***********************/
  if (! AUDIO.begin()) { // initialise the music player
    DISPLAY_.display.error(F("Pas de carte SON?"));
    Debug::print(F("××× ⋅ Couldn't find VS1053, check PINS?"));
    while (1);
  }else{
    AUDIO.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
    Debug::print(F("✓✓✓ ⋅ VS1053 found and started"));
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
    Debug::print(F("××× ⋅ SD failed, or not present"));
    while (1);  // don't do anything more
  }else{
    Debug::print(F("✓✓✓ ⋅ SD Card found "));
  }

  // Définir les callbacks
  SD_BACKUP.setCallbacks(onSDError, onBeforeSDReadWrite, onAfterSDReadWrite , onBeforeSDReadWrite, onAfterSDReadWrite );
  Debug::print(F("✓✓✓ ⋅ FILES ok "));

  if (SD_BACKUP.load(STATE_FILENAME, &STATE, sizeof(STATE))) {
    Debug::print(F("✓✓✓ ⋅ Chargement Etat ok "));
  }else{
    Debug::print(F("××× ⋅ STATE: Pas de chargement"));
  }
  if (SD_BACKUP.load(MARKERS_FILENAME, &DATAS, sizeof(DATAS))) {
    Debug::print(F("✓✓✓ ⋅ Chargement Marqueurs ok "));
  }else{
    Debug::print(F("××× ⋅ MARKERS: Pas de chargement"));
  }

  FILE_.begin(STATE.dirNum, STATE.fileNum); // Initialisation selon carte
  FILE_.setDirCallbacks( onBeforeSelectDir, onAfterSelectDir );
  FILE_.setFileCallbacks( onBeforeSelectFile, onAfterSelectFile );

  SLEEP_WATCH.setCallbacks(onSleep, onWakeUp);
  SLEEP_WATCH.wakeUp();
  Debug::print(F("✓✓✓ ⋅ Sleep Watch ok "));

  /**********************
  * INTERFACE: ROTARIES & BUTTONS  
  ***********************/

  for (byte i = 0; i < 3; ++i) {
    ROTARIES[i].begin(); // Remplacez 2 et 3 par les broches réelles de votre rotary encoder
    ROTARIES[i].setChangedHandler(onRotChange);
  }
  MUX.begin();
  BUTTONS.setCallbacks(onPress,onRelease,onLongPress,onLongRelease);
  Debug::print(F("✓✓✓ ⋅ Interface ok "));
  
  // Play a file in the background, REQUIRES interrupts!  
  AUDIO.startPlayingFile(STARTSOUND);      
  setMode(PLAYER);
  
};