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
    Serial.print(F("FdS Player: "));
    Serial.println(CREDITS);
  }
  /**********************
  * DISPLAY:
  ***********************/
  SCREEN_.begin();
  SCREEN_.switchMode(DisplayManager::MODE_SPLASH);
  /**********************
  * AUDIO:
  ***********************/
  if (! AUDIO.begin()) { // initialise the music player
    Serial.println(F("××× ⋅ Couldn't find VS1053, check PINS?"));
    while (1);
  }else{
    AUDIO.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
    Serial.println(F("✓✓✓ ⋅ VS1053 found and started"));
    // Set volume for left, right channels. lower numbers == louder volume!
    AUDIO.setVolume(VOLUME,VOLUME);
    AUDIO.applyPatch(pluginPitchShifter, PLUGIN_PITCHSHIFTER_SIZE);  
    AUDIO.sciWrite(VS1053_SCI_AIADDR, 0x50);
    PITCHER.setPitchStep(STATE.pitchStep);
    if(ASF_DEBUG_MODE){
      AUDIO.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working
      delay(1000);
    }
  }

  /**********************
  * FILES:
  ***********************/
  if (!SD.begin(CARDCS,SPI_SPEED)) {
    Serial.println(F("××× ⋅ SD failed, or not present"));
    while (1);  // don't do anything more
  }else{
    Serial.println(F("✓✓✓ ⋅ SD Card found: "));
  }

  FILE_.begin(0, 0); // Utilisation avec les fonctions de rappel
  FILE_.setDirCallbacks( onBeforeSelect, onAfterSelect );
  FILE_.setFileCallbacks( onBeforeSelect, onAfterSelect );

  SLEEP_WATCH.setCallbacks(onSleep, onWakeUp);

  /**********************
  * INTERFACE: ROTARIES & BUTTONS
  ***********************/
  for (byte i = 0; i < 3; ++i) {
    ROTARIES[i].begin(); // Remplacez 2 et 3 par les broches réelles de votre rotary encoder
    ROTARIES[i].setChangedHandler(onRotChange);
  }
  MUX.begin();
  BUTTONS.setCallback(onPress);

  // Play a file in the background, REQUIRES interrupts!  
  AUDIO.playFullFile(STARTSOUND);  
};