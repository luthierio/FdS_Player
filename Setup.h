/**********************
* SETUP
***********************/
void setup() {
  /**********************
  * SERIAL:
  ***********************/
  Serial.begin(115200);
  if(SERIAL_WAIT){
    // Wait for serial port to be opened
    while (!Serial) { delay(1); }  
  }
  /**********************
  * DISPLAY:
  ***********************/    
  if(SCREEN_.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){    
    DISPLAY_.init();
    DISPLAY_.display.logo();
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
    DISPLAY_.display.error(F("SD Card Failed"));
    DEBUG_.print(F("××× ⋅ SD failed, or not present"));
    while (1);  // don't do anything more
  }else{
    DEBUG_.print(F("✓✓✓ ⋅ SD Card found "));
  }

  // Définir les callbacks
  SD_FS.setCallbacks(onSDError, onBeforeSDReadWrite, onAfterSDReadWrite , onBeforeSDReadWrite, onAfterSDReadWrite );
  SD_FS.setBackupEnabled(BACKUP_REQUIRED);

  DEBUG_.print(F("✓✓✓ ⋅ FILES ok "));

  FILE_.setDirCallbacks( onBeforeSelectDir, onAfterSelectDir );
  FILE_.setFileCallbacks( onBeforeSelectFile, onAfterSelectFile );

  PLAYLISTS_.setCallbacks( onPlayListConfirm, onPlayListError, onPlayListSetPosition );
  MARKERS_.setCallbacks( onMarkerAdd );

  SLEEP_WATCH.setCallbacks(onSleep, onWakeUp);
  SLEEP_WATCH.wakeUp();
  DEBUG_.print(F("✓✓✓ ⋅ Sleep Watch ok "));

  /**********************
  * INTERFACE: ROTARIES & BUTTONS  
  ***********************/

  for (byte i = 0; i < 3; ++i) {
    ROTARIES[i].begin(); 
    ROTARIES[i].setChangedHandler(onRotChange);
    ROTARIES[i].setLowerOverflowHandler(onRotUpLimit);
    ROTARIES[i].setUpperOverflowHandler(onRotLowLimit);
  }
  MUX.begin();
  BUTTONS.setCallbacks(onPress,onRelease,onLongPress,onLongRelease);
  DEBUG_.print(F("✓✓✓ ⋅ Interface ok "));
  
  SD_FS.load(MARKERS_FILENAME, &MARKERS, sizeof(MARKERS), SILENT);  
  SD_FS.load(PLAYLISTS_FILENAME, &PLAYLISTS, sizeof(PLAYLISTS), SILENT);
  SD_FS.load(STATE_FILENAME, &STATE, sizeof(STATE), SILENT);

  DISPLAY_.display.message(CREDITS);
  DISPLAY_.show();

  // Play a file in the background, REQUIRES interrupts!  
  AUDIO.playFullFile(STARTSOUND);
  
  FILE_.select(STATE.dirNum, STATE.fileNum); // Initialisation selon carte  
  PLAYLISTS_.setPosition( STATE.playlistPosition, SILENT ); 
    
  setMode(STATE.MODE);
  DEBUG_.print(F("Free Ram :") ,FreeRam());
  
};