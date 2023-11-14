/**********************
* SETUP
***********************/
void pausePlaying() {
  AUDIO.pausePlaying(true);
  delay(1);
}

void unpausePlaying() {
  delay(1);
  AUDIO.pausePlaying(false);
}

void onChange(Rotary &rotary) {
  int currentPosition = rotary.getPosition();

    if(&rotary == R_DIR){
      Serial.print("Dir changed: ");
      FILE_.selectDir(currentPosition);
    }
    if(&rotary == R_FILES){
      Serial.print("File changed: "); 
      FILE_.selectFile(currentPosition);
    }
    Serial.print(currentPosition);
    Serial.print(" | "); 
    Serial.print(FILE_.path);
    Serial.println(" | "); 

    if(&rotary == R_PITCH){
      Serial.print("Pitch changed: ");
      Serial.print(currentPosition);
      Serial.print(" / "); 
      STATE.pitchStep = currentPosition;
      PITCHER.setPitchStep(STATE.pitchStep);
      Serial.println(STATE.pitchStep);
    }
    
}
void onPress(ButtonHandler* buttonHandler, int buttonIndex, bool longPress, bool buttonState) {
  // Implémentez le traitement personnalisé ici
  // Exemple : 
  if(!longPress){
    if(buttonIndex == 0 && !buttonState){
      AUDIO.startPlayingFile(FILE_.path);
    }
    if(buttonIndex == 1 && !buttonState){
      if (! AUDIO.paused()) {
        Serial.println("Paused");
        AUDIO.pausePlaying(true);
      } else {
        Serial.println("Resumed");
        AUDIO.pausePlaying(false);
      }
    }
  }
  Serial.print("Button: "); 
  Serial.print(buttonIndex); 
  Serial.print("/");
  if(longPress){
    Serial.print("Long");  
  }else{
    Serial.print("Court");  
  }
  Serial.print("/");
  if(buttonState == HIGH){
    Serial.print("Relaché");  
  }else{
    Serial.print("Pressé");  
  }
  Serial.println("");
}
void setup() {
  if(SERIAL_ON){
    Serial.begin(115200);
    // Wait for serial port to be opened, remove this line for 'standalone' operation
    while (!Serial) { delay(1); }
    Serial.print(F("FdS Player: "));
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
    PITCHER.setPitchStep(STATE.pitchStep);
  }

  if (!SD.begin(CARDCS,SPI_SPEED)) {
    if(SERIAL_ON) Serial.println(F("××× ⋅ SD failed, or not present"));
    while (1);  // don't do anything more
  }else{
    if(SERIAL_ON) Serial.println(F("✓✓✓ ⋅ SD Card found: "));
  }

  FILE_.begin(0, 0); // Utilisation avec les fonctions de rappel
  FILE_.setDirCallbacks(pausePlaying, unpausePlaying);
  FILE_.setFileCallbacks(pausePlaying, unpausePlaying);


  for (byte i = 0; i < 3; ++i) {
    ROTARIES[i].begin(); // Remplacez 2 et 3 par les broches réelles de votre rotary encoder
    ROTARIES[i].setChangedHandler(onChange);
    if(SERIAL_ON) Serial.print(F("Rotary begin: "));
    if(SERIAL_ON) Serial.println(i);
  }
  MUX.begin();
  BUTTONS.setCallback(onPress);

  // Play a file in the background, REQUIRES interrupts!  
  //AUDIO.playFullFile(STARTSOUND);  


};