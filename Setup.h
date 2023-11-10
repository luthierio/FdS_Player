/**********************
* SETUP
***********************/
void setup() {

  if(ASF_DEBUG_MODE){
    Serial.begin(115200);
    // Wait for serial port to be opened, remove this line for 'standalone' operation
    while (!Serial) { delay(1); }
  }

  if(ASF_DEBUG_MODE){
    Serial.print(F("FdS Player: "));
    Serial.print(" - DEBUG MODE - ");
    Serial.println(CREDITS);
  }

  if (! AUDIO.begin()) { // initialise the music player
    if(ASF_DEBUG_MODE) Serial.println(F("××× ⋅ Couldn't find VS1053, check PINS?"));
    while (1);
  }else{
    AUDIO.setVolume(VOLUME,VOLUME);
    AUDIO.applyPatch(pluginPitchShifter, PLUGIN_PITCHSHIFTER_SIZE);  
    AUDIO.sciWrite(VS1053_SCI_AIADDR, 0x50);

    AUDIO.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
    if(ASF_DEBUG_MODE) Serial.println(F("✓✓✓ ⋅ VS1053 found and started"));
    if(ASF_DEBUG_MODE) AUDIO.sineTest(0x44, 1000);    // Make a tone to indicate VS1053 is working
    // Set volume for left, right channels. lower numbers == louder volume!
  }

  if (!SD.begin(CARDCS,SPI_SPEED)) {
    if(ASF_DEBUG_MODE) Serial.println(F("××× ⋅ SD failed, or not present"));
    while (1);  // don't do anything more
  }else{
    if(ASF_DEBUG_MODE) Serial.println(F("✓✓✓ ⋅ SD Card found: "));
  }
  FILE_.begin(&STATE.dirNum,&STATE.fileNum);
  // Play a file in the background, REQUIRES interrupts!  
  AUDIO.playFullFile(STARTSOUND);
  
}