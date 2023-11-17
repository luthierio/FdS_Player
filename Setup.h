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
    Debug::print(F("××× ⋅ Couldn't find VS1053, check PINS?"));
    while (1);
  }else{
    AUDIO.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
    Debug::print(F("✓✓✓ ⋅ VS1053 found and started"));
    //AUDIO.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working
    delay(500);
    PITCHER.init();
    // Set volume for left, right channels. lower numbers == louder volume!
    AUDIO.setVolume(VOLUME,VOLUME);
  }

  /**********************
  * FILES:
  ***********************/
  if (!SD.begin(CARDCS,SPI_SPEED)) {
    Debug::print(F("××× ⋅ SD failed, or not present"));
    while (1);  // don't do anything more
  }else{
    Debug::print(F("✓✓✓ ⋅ SD Card found "));
  }

  FILE_.begin(0, 0); // Utilisation avec les fonctions de rappel
  FILE_.setDirCallbacks( onBeforeSDWork, onAfterSDWork );
  FILE_.setFileCallbacks( onBeforeSDWork, onAfterSDWork );

  // Définir les callbacks
  SD_BACKUP.setCallbacks(onBeforeSDWrite, onAfterSDWork , onBeforeSDWrite, onAfterSDWork );
  Debug::print(F("✓✓✓ ⋅ FILES ok "));

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
  BUTTONS.setCallbacks(onPress,onRelease);
  Debug::print(F("✓✓✓ ⋅ Interface ok "));

  // Play a file in the background, REQUIRES interrupts!  
  AUDIO.startPlayingFile(STARTSOUND);  
  delay(1000);
  setMode(PLAYER);
  
  //SCREEN_.switchMode(DisplayManager::MODE_NAVIGATION);
};