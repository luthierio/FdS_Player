/**********************
* MODE
***********************/
void setMode(uint8_t mode) {
  Debug::print("MODE", mode);
  DISPLAY_.clear();

  switch (mode) {
    case PLAYER:
      DISPLAY_.files.printPath(&FILE_);
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
        Debug::print("ROT",currentPosition);  
        Debug::print("PITCHER Step",PITCHER.getStep());  
        Debug::print("PITCHER Value",PITCHER.getValue());  
      }
      break;   
    case PLAYLIST: 
    case BEAT: 
    case ACTION:   
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
    case PLAYER:
      // Short press
      switch (ID) {
        case 0:
          Debug::print("Playing", FILE_.path);
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

          Debug::print("Bitrate", AUDIO.getBitRate()); 
          Debug::print("Position", AUDIO.getFilePosition());
          if(DATA->markers.isEmpty()){
            JumpPosition = (AUDIO.getFilePosition() >= SECONDS_PER_JUMP * (BITRATE / 8)) ? (AUDIO.getFilePosition() - SECONDS_PER_JUMP * (BITRATE / 8)) : 0;   
          }else{
            //on cherche BITRATE / 4 = 2 seconde pour sauter au rpécédent si on est très proche du marker
            JumpPosition =DATA->markers.getPreviousFrom(AUDIO.getFilePosition()- BITRATE / 4); 
            Debug::print("Jump", DATA->markers.getPreviousFrom(AUDIO.getFilePosition()-BITRATE / 4 ));
          } 
          AUDIO.jumpTo(JumpPosition);
          //AUDIO.startPlayingAtPosition(FILE_.path, JumpPosition);
          Debug::print("Jump Position", JumpPosition);

          break;

        case 3:
          Debug::print("Mode PLAYER");
          setMode(PLAYER);
          break;

        case 4:
          if(STATE.playMode < REPEATONE){STATE.playMode++;}        
          else{STATE.playMode = ONEPLAY;}
          Debug::print("playMode", STATE.playMode);
          break;

        case 5:
          PITCHER.switchSign();
          PITCHER.reset();
          Debug::print("PITCHER", PITCHER.getSign());

          break;
        default:
          break;
      }
      break;
    case PLAYLIST:
    case BEAT:
    case ACTION:
      // Short press
      switch (ID) {
        case 0:
          Debug::print("Load DATA");
          if (SD_BACKUP.load(MARKERS_FILENAME, &DATAS, sizeof(DATAS))) {
            Debug::print("OK", SD_BACKUP.getLastMessage());
          } else {
            Debug::print("ERREUR", SD_BACKUP.getLastMessage());
          }
          break;

        case 1:
          Debug::print("Save DATA");
          if (SD_BACKUP.save(MARKERS_FILENAME, &DATAS, sizeof(DATAS))) {
            Debug::print("OK", SD_BACKUP.getLastMessage());
          } else {
            Debug::print("ERREUR", SD_BACKUP.getLastMessage());
          }
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
  Debug::print("Pressed", ID);
  delay(10);
}
void onLongPress(ButtonHandler* buttonHandler, int ID) {

  switch (ASF_MODE) {
    case PLAYER:
      // Short press
      switch (ID) {
        case 1:
          //On vérifie que le fichier Sélectionné est bien celui qui joue pour ajouter un marqueur
          if(AUDIO.getFilePosition() && AUDIO.currentTrack.size() == FILE_.getSize()){
            DATA->addMarker(&FILE_,&AUDIO);
            AUDIO.pausePlaying(false);
            Debug::print("New marker", static_cast<int>(AUDIO.getFilePosition()));
          }
          break;

        case 2:
          if(AUDIO.getFilePosition() && AUDIO.currentTrack.size() == FILE_.getSize()){
            DATA->markers.popPrevious(AUDIO.getFilePosition());
          }
          break;


        case 4:
          setMode(ACTION);
          break;
        default:
          break;
      }
    default:
      break;
  }
  Debug::print("LongPress", ID);
  
}


void onRelease(ButtonHandler* buttonHandler, int ID) {

  Debug::print("Release", ID);
  //On stocke le Bitrate pour les Jumps après quelques temps de release.
  // Il faut laisser au player une seconde de jeu
  if(ASF_MODE == PLAYER && ID == 0){
    //BITRATE = AUDIO.getBitRate();
    //Debug::print("BitRate", static_cast<int>(BITRATE));
  }
}
void onLongRelease(ButtonHandler* buttonHandler, int ID) {
  Debug::print("LongRelease", ID);
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
        Debug::print("FIN AutoPlay");

      //Il faudrait essayer d'en jouer une autre
      }else if(!AUDIO.playingMusic && !AUDIO.currentTrack){  
        FILE_.selectFile(FILE_.fileNum + 1);
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
  Debug::print("Sleeping");
}
void onWakeUp(){
  SCREEN_.ssd1306_command(SSD1306_DISPLAYON);
  Debug::print("Wakeup");
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
  Debug::print("Selected", FILE_.path); 
}
void onBeforeSDWrite() {
  if(AUDIO.playingMusic){
    MUST_RESUME = true;
    AUDIO.pausePlaying(true);
    delay(100);
  }
}
void onBeforeSelectDir(){
  onBeforeSDWork();
}
void onBeforeSelectFile(){
  onBeforeSDWork();
}
void onAfterSelectDir(){

  onAfterSDWork();
  DATA = &getFileDataRef(FILE_.dirNum,FILE_.fileNum);
  //TODO ?
  //R_DIR->resetPosition(FILE_.dirNum*R_DIR->getStepsPerClick(), false);

  if(ASF_MODE == PLAYER){
    DISPLAY_.files.printPath(&FILE_);
  }

  Debug::print("SelectDir",FILE_.dirNum,FILE_.path);  

}
void onAfterSelectFile(){

  onAfterSDWork();
  DATA = &getFileDataRef(FILE_.dirNum,FILE_.fileNum);
  //TODO ?
  //R_DIR->resetPosition(FILE_.fileNum*R_DIR->getStepsPerClick(), false);

  if(ASF_MODE == PLAYER){
    DISPLAY_.files.printPath(&FILE_);
  }
  
  Debug::print("SelectFile",FILE_.fileNum,FILE_.path);  

}     
