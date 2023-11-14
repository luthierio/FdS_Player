/**********************
* Events
***********************/
bool MUST_RESUME = false;
void onBeforeSelect() {
  if(AUDIO.playingMusic){
    MUST_RESUME = true;
    AUDIO.pausePlaying(true);
    delay(1);
  }
}
void onAfterSelect() {
  delay(1);
  if(MUST_RESUME){
    AUDIO.pausePlaying(false);
    MUST_RESUME = false;
  }
}
void onSleep(){
  SCREEN_.switchOff();
}
void onWakeUp(){
  SCREEN_.switchOn();
}
void onRotChange(Rotary &rotary) {

  SLEEP_WATCH.wakeUp();

  int currentPosition = rotary.getPosition();

  if(&rotary == R_DIR){
    STATE.dirNum = currentPosition;
    FILE_.selectDir(STATE.dirNum);
  }
  if(&rotary == R_FILES){
    STATE.fileNum = currentPosition;
    FILE_.selectFile(STATE.fileNum);
  }

  if(&rotary == R_PITCH){
    STATE.pitchStep = currentPosition;
    PITCHER.setPitchStep(STATE.pitchStep);
  }
  if(SERIAL_ON){
    Serial.print(FILE_.dirNum) ;
    Serial.print(" + ") ;
    Serial.print(FILE_.fileNum) ;
    Serial.print(": ") ;
    Serial.println(FILE_.path) ;
  }
}
void onPress(ButtonHandler* buttonHandler, int buttonIndex, bool longPress, bool buttonState) {
  // Implémentez le traitement personnalisé ici
  // Exemple : 
  
  SLEEP_WATCH.wakeUp();

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
    if(buttonIndex == 2 && !buttonState){
      SCREEN_.switchMode(DisplayManager::MODE_MENU);
    }
    if(buttonIndex == 3 && !buttonState){
      SCREEN_.switchMode(DisplayManager::MODE_SPLASH);
    }
  }
}