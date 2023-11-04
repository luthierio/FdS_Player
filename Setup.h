/**********************
* SETUP
***********************/

void setup() {

  Serial.begin(115200);

  if(ASF_DEBUG_MODE){
    // Wait for serial port to be opened, remove this line for 'standalone' operation
    while (!Serial) { delay(1); }
  }
  delay(500);
  if(ASF_DEBUG_MODE){
    Serial.print(F("FdS Player: "));
    Serial.print(" - DEBUG MODE - ");
    Serial.println(CREDITS);
    delay(500);
  }

  if (! musicPlayer.begin()) { // initialise the music player
    if(ASF_DEBUG_MODE) Serial.println(F("××× ⋅ Couldn't find VS1053, check PINS?"));
    while (1);
  }else{
    musicPlayer.setVolume(10,10);
    musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
    if(ASF_DEBUG_MODE) Serial.println(F("✓✓✓ ⋅ VS1053 found and started"));
    if(ASF_DEBUG_MODE) musicPlayer.sineTest(0x44, 1000);    // Make a tone to indicate VS1053 is working
    // Set volume for left, right channels. lower numbers == louder volume!
  }

  if (!SD.begin(CARDCS,SPI_SPEED)) {
    if(ASF_DEBUG_MODE) Serial.println(F("××× ⋅ SD failed, or not present"));
    while (1);  // don't do anything more
  }else{
    if(ASF_DEBUG_MODE) Serial.println(F("✓✓✓ ⋅ SD Card found: "));
  }

  // Play a file in the background, REQUIRES interrupts!  
  musicPlayer.playFullFile(STARTSOUND);
  if(ASF_DEBUG_MODE) Serial.println(F("✓✓✓ ⋅ PLAYER READY "));
  
}



/**********************
* FILES FUNCTIONS
***********************/

/// File listing helper
void printDirectory(File dir, int numTabs) {
   while(true) {

     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     char filename[100];
     entry.getName(filename,100);
     if (entry.isDirectory()) {
      Serial.print("📁 ");
      Serial.print(filename);
      Serial.println("/");
      printDirectory(entry, numTabs+1);
     } else {
       Serial.print(filename);
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}