/**********************
* MODE
***********************/
void setMode(uint8_t mode) {
  DEBUG_.print("MODE", mode);
  DISPLAY_.clear();

  switch (mode) {
    case PLAYER:
      R_DIR->resetPosition(FILE_.dirNum);
      R_DIR->setLowerBound(MIN_DIR_NUM);
      R_DIR->setUpperBound(MAX_DIR_NUM);
      DISPLAY_.files.printPath(&FILE_);
      break;

    case MENU:
      R_DIR->resetPosition(ACTION_ID);
      R_DIR->setLowerBound(0);
      R_DIR->setUpperBound(NBR_ACTIONS);
      DISPLAY_.menu.print(ACTIONS[ACTION_ID].title, ACTIONS[ACTION_ID].action); 
      break; 

    default:
      DISPLAY_.display.logo();
      break;
  }

  ASF_MODE = mode;
}

/**********************
* ROTARIES:
***********************/
void onRotChange(Rotary &rotary) {

  SLEEP_WATCH.wakeUp();

  int currentPosition = rotary.getPosition();

  switch (ASF_MODE) {
    case PLAYER:            
      if(&rotary == R_DIR) {
        FILE_.selectDir(currentPosition);
      }
      if(&rotary == R_FILES) {
        FILE_.selectFile(currentPosition);
      }
      if(&rotary == R_PITCH) {
        PITCHER.setPitchStep(currentPosition);
        DEBUG_.print("ROT",currentPosition);  
        DEBUG_.print("PITCHER Step",PITCHER.getStep());  
        DEBUG_.print("PITCHER Value",PITCHER.getValue());  
      }
      break;   
    case PLAYLIST: 
    case BEAT: 
    case MENU:  
      DEBUG_.print("ROT",currentPosition);  
      if(&rotary == R_DIR) {
        ACTION_ID = currentPosition;
        DISPLAY_.menu.print(ACTIONS[ACTION_ID].title, ACTIONS[ACTION_ID].action); 
      } 
      break;   
    default:
      break;

  }  
}

/**********************
* BUTTONS:
***********************/
void onPress(ButtonHandler* buttonHandler, int ID) {

  SHOULD_PLAY_NEXT = false;
  SLEEP_WATCH.wakeUp();
  int JumpPosition;

  switch (ASF_MODE) {
    /**********************
    * PLAYER:
    ***********************/
    case PLAYER:
      switch (ID) {
        case 0:
          DEBUG_.print("Playing", FILE_.path);
          AUDIO.startPlayingFile(FILE_.path);
          break;

        case 1:
          if (AUDIO.playingMusic) {
            AUDIO.pausePlaying(true);
            DEBUG_.print("Paused");
          } else {
            AUDIO.pausePlaying(false);
            DEBUG_.print("Resumed");
          }
          break;

        case 2:         

          DEBUG_.print("Bitrate", AUDIO.getBitRate()); 
          DEBUG_.print("Position", AUDIO.getFilePosition());
          if(DATA->markers.isEmpty()){
            JumpPosition = (AUDIO.getFilePosition() >= SECONDS_PER_JUMP * (BITRATE / 8)) ? (AUDIO.getFilePosition() - SECONDS_PER_JUMP * (BITRATE / 8)) : 0;   
          }else{
            //on cherche BITRATE / 4 = 2 seconde pour sauter au rpécédent si on est très proche du marker
            JumpPosition =DATA->markers.getPreviousFrom(AUDIO.getFilePosition()- BITRATE / 4); 
            DEBUG_.print("Jump", DATA->markers.getPreviousFrom(AUDIO.getFilePosition()-BITRATE / 4 ));
          } 
          AUDIO.jumpTo(JumpPosition);
          DEBUG_.print("Jump Position", JumpPosition);

          break;

        case 3:
          setMode(PLAYLIST);
          break;

        case 4:
          if(STATE.playMode < REPEATONE){STATE.playMode++;}        
          else{STATE.playMode = ONEPLAY;}
          DEBUG_.print("playMode", STATE.playMode);
          break;

        case 5:
          PITCHER.switchSign();
          PITCHER.reset();
          DEBUG_.print("PITCHER", PITCHER.getSign());

          break;
        default:
          break;
      }
      break;
    /**********************
    * PLAYLIST:
    ***********************/
    case PLAYLIST:
      switch (ID) {
        case 3:
          setMode(PLAYER);
          break;
        default:
          break;
      }
    case BEAT:
    /**********************
    * ACTION:
    ***********************/
    case MENU:
      switch (ID) {
        case 0:
        case 1:
        case 2:
          doAction(ACTIONS[ACTION_ID].id);
          break;
        case 4:
          setMode(PLAYER);
          break;
        default:
          break;
      }
    default:
      break;
  }
  DEBUG_.print("Pressed", ID);
  delay(10);
}
void onLongPress(ButtonHandler* buttonHandler, int ID) {

  switch (ASF_MODE) {
    case PLAYER:
      // Short press
      switch (ID) {
        case 0:
          //SD_BACKUP.save(MARKERS_FILENAME, &DATAS, sizeof(DATAS));
          SD_BACKUP.save(STATE_FILENAME, &STATE, sizeof(STATE));
          break;
        case 1:
          //On vérifie que le fichier Sélectionné est bien celui qui joue pour ajouter un marqueur
          if(AUDIO.getFilePosition() && AUDIO.currentTrack.size() == FILE_.getSize()){
            DATA->addMarker(&FILE_,&AUDIO);
            AUDIO.pausePlaying(false);
            DEBUG_.print("New marker", static_cast<int>(AUDIO.getFilePosition()));
          }
          break;

        case 2:
          if(AUDIO.getFilePosition() && AUDIO.currentTrack.size() == FILE_.getSize()){
            DATA->markers.popPrevious(AUDIO.getFilePosition());
          }
          break;

        case 4:
          setMode(MENU);
          break;
        default:
          break;
      }
    default:
      break;
  }
  DEBUG_.print("LongPress", ID);
  
}


void onRelease(ButtonHandler* buttonHandler, int ID) {

  switch (ASF_MODE) {
    /**********************
    * PLAYER:
    ***********************/
    case PLAYER:
      switch (ID) {
        case 0:
          break;
      }
  }
  DEBUG_.print("Release", ID);
}
void onLongRelease(ButtonHandler* buttonHandler, int ID) {
  DEBUG_.print("LongRelease", ID);
}

/**********************
* AUTOPLAY:
***********************/
void autoPlay(){

  if(STATE.playMode != ONEPLAY){

    //La fin d'un fichier forcera l'autoplay à se lancer dès que la musique est finie!    
    if(AUDIO.playingMusic && ((AUDIO.currentTrack.size()-AUDIO.getFilePosition()) < 5000)){    
        SHOULD_PLAY_NEXT = true;
    }

    if(SHOULD_PLAY_NEXT && ASF_MODE == PLAYER) {

      //Fin du répertoire
      if(FILE_.fileNum == 99){    
        FILE_.selectFile(0);
        SHOULD_PLAY_NEXT = false;
        DEBUG_.print("FIN AutoPlay");

      //Il faudrait essayer d'en jouer une autre
      }else if(!AUDIO.playingMusic && !AUDIO.currentTrack){  
        switch (STATE.playMode) {
          case AUTO:
            FILE_.selectFile(FILE_.fileNum + 1);
            break;
          case RANDOM:
            FILE_.selectFile(random(0, 99));
            break;
          case REPEATONE:
            break;
          default:
            //Not necessary but secure
            SHOULD_PLAY_NEXT = false;
            break;
        }
        AUDIO.startPlayingFile(FILE_.path); 
      }
          
    }
  }

}

/**********************
* SLEEP:
***********************/
void onSleep(){
  SCREEN_.ssd1306_command(SSD1306_DISPLAYOFF);
  DEBUG_.print("Sleeping");
}
void onWakeUp(){
  SCREEN_.ssd1306_command(SSD1306_DISPLAYON);
  DEBUG_.print("Wakeup");
}

/**********************
* VOLUME:
***********************/
void setVolume(uint8_t reqVolume) {
  
  if(reqVolume != VOLUME && reqVolume >= MIN_VOLUME-1){

    VOLUME = MIN_VOLUME;
    SLEEP_WATCH.wakeUp();
    AUDIO.setVolume(254,254); // VOL MIN doit etre sur off = 255   

  }else if(reqVolume != VOLUME && abs(reqVolume - VOLUME) > 2){  

    VOLUME = reqVolume;
    SLEEP_WATCH.wakeUp();
    AUDIO.setVolume(VOLUME,VOLUME); 

  }

}
/**********************
* FILEPICKER:
* MANAGER:
***********************/


bool MUST_RESUME = false;
void onBeforeSDWork() {

  if(AUDIO.playingMusic){
    MUST_RESUME = true;
    AUDIO.pausePlaying(true);
  }
  
}
void onAfterSDWork() {
  if(MUST_RESUME){ 
    AUDIO.pausePlaying(false);
    MUST_RESUME = false;
  }
  DEBUG_.print("Selected", FILE_.path); 
}
void onBeforeSDReadWrite(const char* fileName, const char* message) {
  DEBUG_.print("SD", fileName, message); 
  DISPLAY_.display.message(fileName);
  //onMessage("Opération SD en cours");
  //On Stoppe le player avant toute écriture, pour éviter les problèmes
  AUDIO.stopPlaying();
  delay(10);
}
void onAfterSDReadWrite(const char* fileName, const char* message) {
  DEBUG_.print("✓✓✓ ⋅ ", fileName, message); 
  onAfterSDWork();
  DISPLAY_.display.message(message);
  delay(MSG_DELAY);
  setMode(ASF_MODE);
}
void onSDError(const char* fileName, const char* message) {
  DEBUG_.print("××× ⋅ ", fileName, message); 
  onAfterSDWork();
  DISPLAY_.display.message(message);
  delay(ERROR_MSG_DELAY);
  setMode(ASF_MODE);
}



void onBeforeSelectDir(){
  onBeforeSDWork();
}
void onBeforeSelectFile(){
  onBeforeSDWork();
}
void onAfterSelectDir(){

  onAfterSDWork();
  STATE.dirNum = FILE_.dirNum;
  DATA = &getFileDataRef(FILE_.dirNum,FILE_.fileNum);
  //TODO ?
  //R_DIR->resetPosition(FILE_.dirNum*R_DIR->getStepsPerClick(), false);

  if(ASF_MODE == PLAYER){
    DISPLAY_.files.printPath(&FILE_);
  }

  DEBUG_.print("SelectDir",FILE_.dirNum,FILE_.path);  

}
void onAfterSelectFile(){

  onAfterSDWork();
  STATE.fileNum = FILE_.fileNum;
  DATA = &getFileDataRef(FILE_.dirNum,FILE_.fileNum);
  //TODO ?
  //R_DIR->resetPosition(FILE_.fileNum*R_DIR->getStepsPerClick(), false);

  if(ASF_MODE == PLAYER){
    DISPLAY_.files.printPath(&FILE_);
  }
  
  DEBUG_.print("SelectFile",FILE_.fileNum,FILE_.path);  

}
