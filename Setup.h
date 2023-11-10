/**********************
* SETUP
***********************/
void setup() {

  if(SERIAL_ON){
    Serial.begin(115200);
    // Wait for serial port to be opened, remove this line for 'standalone' operation
    while (!Serial) { delay(1); }
    Serial.print(F("FdS Player: "));
    Serial.print(" - DEBUG MODE - ");
    Serial.println(CREDITS);
  }

  if (! AUDIO.begin()) { // initialise the music player
    if(SERIAL_ON) Serial.println(F("××× ⋅ Couldn't find VS1053, check PINS?"));
    while (1);
  }else{

    AUDIO.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
    if(SERIAL_ON) Serial.println(F("✓✓✓ ⋅ VS1053 found and started"));
    // Set volume for left, right channels. lower numbers == louder volume!
    AUDIO.setVolume(VOLUME,VOLUME);
    if(SERIAL_ON){
      AUDIO.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working
      delay(1000);
    }
    AUDIO.applyPatch(pluginPitchShifter, PLUGIN_PITCHSHIFTER_SIZE);  
    AUDIO.sciWrite(VS1053_SCI_AIADDR, 0x50);
    PITCHER.setPitchStep(STATE.pitchStep.val);
  }

  if (!SD.begin(CARDCS,SPI_SPEED)) {
    if(SERIAL_ON) Serial.println(F("××× ⋅ SD failed, or not present"));
    while (1);  // don't do anything more
  }else{
    if(SERIAL_ON) Serial.println(F("✓✓✓ ⋅ SD Card found: "));
  }
  FILE_.begin(&STATE.dirNum,&STATE.fileNum);
  // Play a file in the background, REQUIRES interrupts!  
  AUDIO.playFullFile(STARTSOUND);
  
}