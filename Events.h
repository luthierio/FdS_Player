/**********************
* MODE
***********************/

void setMode(uint8_t mode){

  Debug::print("MODE", mode);

  if(mode != ASF_MODE){

    DISPLAY_.clear();

    switch (mode) {
      case PLAYER:
        DISPLAY_.printPath(&FILE_);
      break;   

      case ACTION:
        DISPLAY_.logo();
      break;   
    }  

    ASF_MODE = mode;

  }
  
}

/**********************
* ROTARIES:
***********************/
void onRotChange(Rotary &rotary) {

  SLEEP_WATCH.wakeUp();

  int currentPosition = rotary.getPosition();

  switch (ASF_MODE) {
    case PLAYER: 
    case PLAYLIST: 
    case BEAT: 
    case ACTION:              
      if(&rotary == R_DIR) {
        FILE_.selectDir(currentPosition);
        STATE.dirNum = currentPosition;
        DISPLAY_.printPath(&FILE_);
      }
      if(&rotary == R_FILES) {
        FILE_.selectFile(currentPosition);
        STATE.fileNum = currentPosition;
        DISPLAY_.printPath(&FILE_);
      }
      if(&rotary == R_PITCH) {
        PITCHER.setPitchStep(currentPosition);
      }
      Debug::print("ROT",currentPosition, FILE_.path);  
    break;   
  }  
}

/**********************
* BUTTONS:
***********************/
void onPress(ButtonHandler* buttonHandler, int ID, bool LONG) {

  SLEEP_WATCH.wakeUp();
  int Jump;

  switch (ASF_MODE) {
    case PLAYER:
    case PLAYLIST:
    case BEAT:
    case ACTION:
      switch (LONG) {
        // Short press
        case false:
          switch (ID) {
            case 0:
              Debug::print("Playing");
              BITRATE = 0;
              AUDIO.startPlayingFile(FILE_.path);
              break;

            case 1:
              if (AUDIO.playingMusic) {
                AUDIO.pausePlaying(true);
                Debug::print("Paused");
              } else {
                AUDIO.pausePlaying(false);
                Debug::print("Resumed");
              }
              break;

            case 2:         
              Jump = SECONDS_PER_JUMP*(BITRATE / 8);
              if(BITRATE && Jump > AUDIO.getFilePosition()){
                AUDIO.startPlayingAtPosition(FILE_.path, AUDIO.getFilePosition()- Jump);
                Debug::print("Jump", static_cast<int>(Jump));
              }else{
                AUDIO.startPlayingFile(FILE_.path);
              }
              delay(100);

              break;

            case 3:
              Debug::print("Mode PLAYER");
              setMode(PLAYER);
              break;

            case 4:
              Debug::print("Load DATA");
              if (SD_BACKUP.load(STATE_FILENAME, &STATE, sizeof(STATE))) {
                Debug::print("OK", SD_BACKUP.getLastMessage());
              } else {
                Debug::print("ERREUR", SD_BACKUP.getLastMessage());
              }
              Debug::print("DirNum", STATE.dirNum);
              break;

            case 5:
              Debug::print("Save DATA");
              if (SD_BACKUP.save(STATE_FILENAME, &STATE, sizeof(STATE))) {
                Debug::print("OK", SD_BACKUP.getLastMessage());
              } else {
                Debug::print("ERREUR", SD_BACKUP.getLastMessage());
              }
              Debug::print("DirNum", STATE.dirNum);
              break;
          }
          break;

        // Long press
        case true:
          break;
      }

      break;
  }
  Debug::print("Pressed", ID, LONG);
}


void onRelease(ButtonHandler* buttonHandler, int ID, bool LONG) {

  //On stocke le Bitrate pour les Jumps après quelques temps de release.
  // Il faut laisser au player une seconde de jeu
  if(ASF_MODE == PLAYER && ID == 0 && LONG){
    BITRATE = AUDIO.getBitRate();
    Debug::print("BitRate", static_cast<int>(BITRATE));
  }
}

/**********************
* SLEEP:
***********************/
void onSleep(){
  SCREEN_.ssd1306_command(SSD1306_DISPLAYOFF);
  Debug::print("Sleeping");
}
void onWakeUp(){
  SCREEN_.ssd1306_command(SSD1306_DISPLAYON);
  Debug::print("Wakeup");
}

/**********************
* FILEPICKER:
***********************/
bool MUST_RESUME = false;
void onBeforeSDWork() {
  if(AUDIO.playingMusic){
    MUST_RESUME = true;
    AUDIO.pausePlaying(true);
    delay(5);
  }
}
void onAfterSDWork() {
  delay(5);
  if(MUST_RESUME){ 
    AUDIO.pausePlaying(false);
    MUST_RESUME = false;
  }
}
void onBeforeSDWrite() {
  if(AUDIO.playingMusic){
    MUST_RESUME = true;
    AUDIO.pausePlaying(true);
    delay(100);
  }
}
