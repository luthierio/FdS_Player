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
  //SCREEN_.switchOff();
  SCREEN_.ssd1306_command(SSD1306_DISPLAYOFF);
  Debug::print("Sleeping");
}
void onWakeUp(){
  //SCREEN_.switchOn();
  SCREEN_.ssd1306_command(SSD1306_DISPLAYON);
  Debug::print("Wakeup");
}
void onRotChange(Rotary &rotary) {

  SLEEP_WATCH.wakeUp();

  int currentPosition = rotary.getPosition();

  switch (ASF_MODE) {
    case PLAYER: {                   
      if(&rotary == R_DIR) {
        STATE.dirNum = currentPosition;
        FILE_.selectDir(STATE.dirNum);
      }
      if(&rotary == R_FILES) {
        STATE.fileNum = currentPosition;
        FILE_.selectFile(STATE.fileNum);
      }
      if(&rotary == R_PITCH) {
        STATE.pitchStep = currentPosition;
        PITCHER.setPitchStep(STATE.pitchStep);
      }
      Debug::print("ROT",currentPosition, FILE_.path);
    }
  }  
}

void onPress(ButtonHandler* buttonHandler, int ID, bool LONG) {  
  SLEEP_WATCH.wakeUp();

  switch (ASF_MODE) {

    case PLAYER: 

      switch (ID){

        case 0: 

          switch (LONG) 
            case true:
            case false:
              Debug::print("Playing");
              AUDIO.startPlayingFile(FILE_.path);
            break;   

        case 1:   

          switch (LONG) 
            case true:
            case false:
              if (AUDIO.playingMusic) {
                AUDIO.pausePlaying(true);
                Debug::print("Paused");
              } else {
                AUDIO.pausePlaying(false);
                Debug::print("Resumed");
              } 
            break;   

        case 2:  
          switch (LONG) 
            case true:
            case false:
              Debug::print("Jumping");
            break;   

      }

    break;   

  }
  Debug::print("Pressed", ID, LONG);
}
void onRelease(ButtonHandler* buttonHandler, int ID, bool LONG) {
  Debug::print("Released", ID, LONG);
  /*
  if(SERIAL_ON) Serial.print("RELEASE ");
  if(SERIAL_ON) Serial.print(ID);
  if(SERIAL_ON) Serial.print(": ");
  if(longPress) Serial.print(" LONG ");
  if(SERIAL_ON) Serial.println("!");
    */
}