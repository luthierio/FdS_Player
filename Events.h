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
  if(SERIAL_ON) Serial.println("Sleeping");
}
void onWakeUp(){
  //SCREEN_.switchOn();
  SCREEN_.ssd1306_command(SSD1306_DISPLAYON);
  if(SERIAL_ON) Serial.println("Wakeup");
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
      if(SERIAL_ON){
        Serial.print(STATE.pitchStep);
        Serial.print(" ");
        Serial.print(STATE.dirNum);
        Serial.print(" ");
        Serial.print(STATE.fileNum);
        Serial.print(": ");
        Serial.println(FILE_.path);
      }
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
              Serial.println("Playing");
              /*
              if(SERIAL_ON) Serial.println("Playing");
              AUDIO.startPlayingFile(FILE_.path);
              */
            break;   

        case 1:   

          switch (LONG) 
            case true:
            case false:
              Serial.println("Pausing");
            break;   
              /*
              if (!AUDIO.playingMusic) {
                AUDIO.pausePlaying(true);
                if(SERIAL_ON) Serial.println("Paused");
              } else {
                AUDIO.pausePlaying(false);
                if(SERIAL_ON) Serial.println("Resumed");
              } 
              */

        case 2:  
          switch (LONG) 
            case true:
            case false:
              Serial.println("Jumping");
            break;   

      }

    break;   

  }
  if(SERIAL_ON){
    Serial.print("PRESS ");
    Serial.print(ID);
    Serial.print(": ");
    if(LONG) Serial.print(" LONG ");
    Serial.println("!");
  }
}
void onRelease(ButtonHandler* buttonHandler, int ID, bool longPress) {
  /*
  if(SERIAL_ON) Serial.print("RELEASE ");
  if(SERIAL_ON) Serial.print(ID);
  if(SERIAL_ON) Serial.print(": ");
  if(longPress) Serial.print(" LONG ");
  if(SERIAL_ON) Serial.println("!");
    */
}