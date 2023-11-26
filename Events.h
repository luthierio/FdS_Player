
/**********************
* MODE:
***********************/
void refreshDisplay() {

  if (STATE.MODE == PLAYER) {

      DISPLAY_.files.printPath(&FILE_, &MP3); 
  
  } else if (STATE.MODE == MENU) {

      DISPLAY_.menu.show(ACTIONS[ACTION_ID].title, ACTIONS[ACTION_ID].action); 

  } else if (STATE.MODE == PLAYLIST) {

      DISPLAY_.playlists.show(); 

  } else if (STATE.MODE == LOGO) {

      DISPLAY_.display.logo();

  }
  DISPLAY_.show();

}
void setMode(uint8_t mode) {
  DEBUG_.print("MODE", mode);
  //DISPLAY_.clear();

  if (mode == PLAYER) {

      R_DIR->resetPosition(FILE_.dirNum, false);
      R_DIR->setUpperBound(MAX_DIR_NUM);
      R_FILES->resetPosition(FILE_.fileNum, false);
      R_FILES->setUpperBound(MAX_FILES_NUM);
  
  } else if (mode == MENU) {
    
      R_DIR->resetPosition(ACTION_ID, false);
      R_DIR->setUpperBound(NBR_ACTIONS);

  } else if (mode == PLAYLIST) {

      R_DIR->resetPosition(PLAYLISTS_.getPosition()[0], false);
      R_DIR->setUpperBound(NBR_PLAYLISTS);
      R_FILES->resetPosition(PLAYLISTS_.getPosition()[1], false);
      R_FILES->setUpperBound(NBR_PLAYLIST_ITEMS);

  }
  
  STATE.MODE = mode;
  refreshDisplay();
}
/**********************
* MESSAGE:
***********************/
void sendMessage(const char* label, const char* message, int DELAY) {
  DEBUG_.print(label, message); 
  DISPLAY_.display.message(message);
  delay(DELAY);
  //setMode(STATE.MODE);
}
/**********************
* ROTARIES:
***********************/
void onRotChange(Rotary &rotary) {

  SLEEP_WATCH.wakeUp();

  int currentPosition = rotary.getPosition();

  /**********************
  * PLAYER:
  ***********************/
  if (STATE.MODE == PLAYER) {

      if(&rotary == R_DIR) {
        FILE_.selectDir(currentPosition);
      }
      if(&rotary == R_FILES) {
        FILE_.selectFile(currentPosition);
      }
      if(&rotary == R_PITCH) {
        PITCHER.setPitchStep(currentPosition);
      }   

  /**********************
  * PLAYLIST:
  ***********************/
  } else if (STATE.MODE == PLAYLIST) {

      if(&rotary == R_DIR) {
        PLAYLISTS_.setPosition(currentPosition); 
      }
      if(&rotary == R_FILES) {
        PLAYLISTS_.setPlayPosition(currentPosition);
      }
       

  /**********************
  * MENU:
  ***********************/
  } else if (STATE.MODE == MENU) {

      DEBUG_.print("ROT",currentPosition);  
      if(&rotary == R_DIR) {
        ACTION_ID = currentPosition;
        DISPLAY_.menu.show(ACTIONS[ACTION_ID].title, ACTIONS[ACTION_ID].action); 
      } 

  }  
}

void onRotUpLimit(Rotary &rotary) {
}
void onRotLowLimit(Rotary &rotary) {  
}

/**********************
* BUTTONS:
***********************/
void onPress(ButtonHandler* buttonHandler, int ID) {

  SHOULD_PLAY_NEXT = false;
  SLEEP_WATCH.wakeUp();
  int JumpPosition;

  /**********************
  * PLAYER:
  ***********************/
  if (STATE.MODE == PLAYER) {

      switch (ID) {
        case 0:
          //Play on release
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

          DEBUG_.print("MARKERS_.isEmpty()", MARKERS_.isEmpty());

          if(MARKERS_.isEmpty()){

            DEBUG_.print("Position", AUDIO.getFilePosition());
            DEBUG_.print("MP3 bps", MP3.getBytePerSecond());
            DEBUG_.print("NEW", (AUDIO.getFilePosition() - MP3.getBytePerSecond()*SECONDS_PER_JUMP) );

            //JumpPosition = (AUDIO.getFilePosition() >= SECONDS_PER_JUMP * (BITRATE / 8)) ? (AUDIO.getFilePosition() - SECONDS_PER_JUMP * (BITRATE / 8)) : 0;   
          }else{
            //on cherche BITRATE / 4 = 2 seconde pour sauter au rpécédent si on est très proche du marker
            JumpPosition =MARKERS_.getPrevious(AUDIO.getFilePosition()- BITRATE / 4); 
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

  /**********************
  * PLAYLIST:
  ***********************/
  } else if (STATE.MODE == PLAYLIST) {

      switch (ID) {
        case 0:
          //Play on Release
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
          break;
        case 3:
          setMode(PLAYER);
          break;
        case 4:
          if(STATE.playlistMode < REPEATONE){STATE.playlistMode++;}        
          else{STATE.playlistMode = ONEPLAY;}
          DISPLAY_.playlists.playList(); 
          DEBUG_.print("playlistMode", STATE.playlistMode);
          break;
        case 5:
          PLAYLISTS_.addCurrentFile(&FILE_);
          DISPLAY_.playlists.playList(); 
          break;
        default:
          break;
      }

  /**********************
  * METRONOME:
  ***********************/
  } else if (STATE.MODE == BEAT) {

      setMode(PLAYER);

  /**********************
  * ACTION:
  ***********************/
  } else if (STATE.MODE == MENU) {

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

  }
  DEBUG_.print("MODE", STATE.MODE);
  DEBUG_.print("Pressed", ID);
  delay(10);
}
void onLongPress(ButtonHandler* buttonHandler, int ID) {

  /**********************
  * PLAYER:
  ***********************/
  if (STATE.MODE == PLAYER) {

      // Long press
      switch (ID) {
        case 0:
          if(!MARKERS_.isEmpty()){
            SD_FS.save(MARKERS_FILENAME, &MARKERS, sizeof(MARKERS));
          }
          SD_FS.save(STATE_FILENAME, &STATE, sizeof(STATE));
          refreshDisplay();
          break;
        case 1:
          //On vérifie que le fichier Sélectionné est bien celui qui joue pour ajouter un marqueur
          if(AUDIO.getFilePosition() && AUDIO.currentTrack.size() == FILE_.getSize()){
            MARKERS_.addMarker(AUDIO.getFilePosition());
            AUDIO.pausePlaying(false);
          }
          break;

        case 2:
          if(AUDIO.getFilePosition() && AUDIO.currentTrack.size() == FILE_.getSize()){
            MARKERS_.deletePrevious(AUDIO.getFilePosition());
          }
          break;

        case 5:
          setMode(MENU);
          break;
        default:
          break;
      }

  /**********************
  * PLAYLIST:
  ***********************/
  } else if (STATE.MODE == PLAYLIST) {

      // Long press
      switch (ID) {
        case 0:
          SD_FS.save(STATE_FILENAME, &STATE, sizeof(STATE));
          SD_FS.save(PLAYLISTS_FILENAME, &PLAYLISTS, sizeof(PLAYLISTS));
          refreshDisplay();
          break;
        case 5:
          break;
        default:
          break;
      }

  } 
  
  DEBUG_.print("LongPress", ID);
  
}


void onRelease(ButtonHandler* buttonHandler, int ID) {

  /**********************
  * PLAYER:
  ***********************/
  if (STATE.MODE == PLAYER) {
      switch (ID) {
        case 0:
          DEBUG_.print("Playing", FILE_.path);
          AUDIO.startPlayingFile(FILE_.path);
          break;
        default:
          break;
      }

  /**********************
  * PLAYLIST:
  ***********************/
  } else if (STATE.MODE == PLAYLIST) {

      switch (ID) {
        case 0:
          DEBUG_.print("dirNum",PLAYLISTS_.getItem()->dirNum);
          DEBUG_.print("fileNum",PLAYLISTS_.getItem()->fileNum);
          if(!PLAYLISTS_.currentPositionIsEmpty()){
            PLAYLISTS_.selectFile(&FILE_);
            AUDIO.startPlayingFile(FILE_.path);
          }
          break;
        default:
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

  bool AUTOPLAY_ON = (STATE.MODE == PLAYER && STATE.playMode != ONEPLAY) || (STATE.MODE == PLAYLIST && STATE.playlistMode != ONEPLAY) ;
  
  if(AUTOPLAY_ON){

    //La fin d'un fichier forcera l'autoplay à se lancer dès que la musique est finie!    
    if(AUDIO.playingMusic && ((AUDIO.currentTrack.size()-AUDIO.getFilePosition()) < 5000)){    
        SHOULD_PLAY_NEXT = true;
    }

    //PLAYER AUTOPLAY
    if(SHOULD_PLAY_NEXT && STATE.MODE == PLAYER) {
          
      //Fin du répertoire
      if(STATE.playMode == AUTO && FILE_.fileNum == MAX_FILES_NUM-1){    
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
            FILE_.selectFile(random(0, MAX_FILES_NUM));
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
    //PLAYLIST AUTOPLAY
    } else if(SHOULD_PLAY_NEXT && STATE.MODE == PLAYLIST) {

      //Fin du répertoire dans la lecture en
      if(STATE.playlistMode == AUTO && PLAYLISTS_.getPlayPosition() == NBR_PLAYLIST_ITEMS-1){    
        PLAYLISTS_.setPlayPosition(0);
        SHOULD_PLAY_NEXT = false;
        DEBUG_.print("FIN AutoPlay");

      //Il faudrait essayer d'en jouer une autre
      }else if(!AUDIO.playingMusic && !AUDIO.currentTrack){  
        switch (STATE.playlistMode) {
          case AUTO:  
            PLAYLISTS_.setPlayPosition(PLAYLISTS_.getPlayPosition()+1);
            break;
          case RANDOM:
            PLAYLISTS_.setPlayPosition(random(0, NBR_PLAYLIST_ITEMS));
            break;
          case REPEATONE:
            break;
          default:
            //Not necessary but secure
            SHOULD_PLAY_NEXT = false;
            break;
        }        
        if(!PLAYLISTS_.currentPositionIsEmpty() && PLAYLISTS_.selectFile(&FILE_)){
          AUDIO.startPlayingFile(FILE_.path); 
        }
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
}
void onBeforeSDReadWrite(const char* fileName, const char* message) {
  INTERRUPTS = false;
  sendMessage(fileName, message,0);
  AUDIO.stopPlaying();
  delay(10);
}
void onAfterSDReadWrite(const char* fileName, const char* message) {
  onAfterSDWork();
  sendMessage(fileName, message,MSG_DELAY);
  INTERRUPTS = true;
}
void onSDError(const char* fileName, const char* message) {
  onAfterSDWork();
  sendMessage(fileName, message,ERROR_MSG_DELAY);
  INTERRUPTS = true;
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
  MARKERS_.selectArray();

  if(STATE.MODE == PLAYER){
    DISPLAY_.files.printPath(&FILE_, &MP3);
  }

  DEBUG_.print("SelectDir",FILE_.dirNum,FILE_.path);  

}
void onAfterSelectFile(){

  onAfterSDWork();
  STATE.fileNum = FILE_.fileNum;
  MARKERS_.selectArray();
  MP3.open(FILE_.path);
  MP3.close();

  if(STATE.MODE == PLAYER){
    DISPLAY_.files.printPath(&FILE_, &MP3);
  }
  
  DEBUG_.print("SelectFile",FILE_.fileNum,FILE_.path);  

}

/**********************
* PLAYLISTS:
***********************/
void onSetPosition(uint8_t position[2]){
  STATE.playlistPosition[0] = position[0];
  STATE.playlistPosition[1] = position[1];
  DISPLAY_.playlists.nav(); 
  DISPLAY_.playlists.playList(); 
}
/**********************
* MARKERS:
***********************/
void onMarkerAdd(uint32_t position){
}
