
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
  DEBUG_.print(F("MODE"), mode);
  //DISPLAY_.clear();

  if (mode == PLAYER) {

      R_DIR->resetPosition(FILE_.dirNum, false);
      R_DIR->setUpperBound(MAX_DIR_NUM);
      R_FILES->resetPosition(FILE_.fileNum, false);
      R_FILES->setUpperBound(MAX_FILES_NUM);
      R_DIR->setCanLoop(true);
      R_FILES->setCanLoop(true);
  
  } else if (mode == PLAYLIST) {

      R_DIR->resetPosition(PLAYLISTS_.getPlayListPosition(), false);
      R_DIR->setUpperBound(NBR_PLAYLISTS-1);
      R_FILES->resetPosition(PLAYLISTS_.getPlayPosition(), false);
      R_FILES->setUpperBound(NBR_PLAYLIST_ITEMS-1);
      R_DIR->setCanLoop(false);
      R_FILES->setCanLoop(false);

  } else if (mode == MENU) {
    
      R_DIR->resetPosition(ACTION_ID, false);
      R_DIR->setUpperBound(NBR_ACTIONS);
      R_DIR->setCanLoop(true);
      R_FILES->setCanLoop(true);

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
void sendMessage(const char* label, const __FlashStringHelper* message, int DELAY) {
  DEBUG_.print(label, message); 
  DISPLAY_.display.message(message);
  delay(DELAY);
  //setMode(STATE.MODE);
}
void sendMessage(const __FlashStringHelper* label, const char* message, int DELAY) {
  DEBUG_.print(label, message); 
  DISPLAY_.display.message(message);
  delay(DELAY);
  //setMode(STATE.MODE);
}
void sendMessage(const __FlashStringHelper* label, const __FlashStringHelper* message, int DELAY) {
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
        FILE_.selectFile(STATE.fileNum); //onAfterSDWork();
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
        PLAYLISTS_.setPlaylistPosition(currentPosition); 
      }
      if(&rotary == R_FILES) {
        PLAYLISTS_.setPlayPosition(currentPosition);
      }
       

  /**********************
  * MENU:
  ***********************/
  } else if (STATE.MODE == MENU) {

      DEBUG_.print(F("ROT"),currentPosition);  
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
          } else {
            AUDIO.pausePlaying(false);
          }
          break;

        case 2:         

          if(MARKERS_.isEmpty()){

            uint32_t jump = MP3.getBytePerSecond()*SECONDS_PER_JUMP;
            JumpPosition = AUDIO.getFilePosition() - jump > 0? AUDIO.getFilePosition() - jump : 0;  

          }else{
            //on cherche 1 seconde en arrière pour sauter au précédent si on est très proche du marker
            JumpPosition =MARKERS_.getPrevious(AUDIO.getFilePosition()- MP3.getBytePerSecond()); 
          } 
          AUDIO.jumpTo(JumpPosition);

          break;

        case 3:
          setMode(PLAYLIST);
          break;

        case 4:
          if(STATE.playMode < REPEATONE){STATE.playMode++;}        
          else{STATE.playMode = ONEPLAY;}
          break;

        case 5:
          PITCHER.switchSign();
          PITCHER.reset();
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
          } else {
            AUDIO.pausePlaying(false);
          }
          break;
        case 2:
          setMode(MENU);
          break;
        case 3:
          setMode(PLAYER);
          break;
        case 4:
          if(STATE.playlistMode < REPEATONE){STATE.playlistMode++;}        
          else{STATE.playlistMode = ONEPLAY;}
          DISPLAY_.playlists.playList(); 
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
  DEBUG_.print(F("MODE"), STATE.MODE);
  DEBUG_.print(F("Pressed"), ID);
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
          PLAYLISTS_.loadM3U(&FILE_);
          break;
        default:
          break;
      }

  } 
  
  DEBUG_.print(F("LongPress"), ID);
  
}


void onRelease(ButtonHandler* buttonHandler, int ID) {

  /**********************
  * PLAYER:
  ***********************/
  if (STATE.MODE == PLAYER) {
      switch (ID) {
        case 0:
          DEBUG_.print(F("Playing"), FILE_.path);
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
          if(!PLAYLISTS_.currentPositionIsEmpty()){
            FILE_.select(PLAYLISTS_.current->dirNum, PLAYLISTS_.current->fileNum);
            AUDIO.startPlayingFile(FILE_.path);
          }
          break;
        default:
          break;
      }

  }
  DEBUG_.print(F("Release"), ID);
}
void onLongRelease(ButtonHandler* buttonHandler, int ID) {
  DEBUG_.print(F("LongRelease"), ID);
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
        DEBUG_.print(F("FIN AutoPlay"));

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
        DEBUG_.print(F("FIN AutoPlay"));

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
        if(!PLAYLISTS_.currentPositionIsEmpty()){
          FILE_.select(PLAYLISTS_.current->dirNum, PLAYLISTS_.current->fileNum);
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
  DEBUG_.print(F("Sleeping"));
}
void onWakeUp(){
  SCREEN_.ssd1306_command(SSD1306_DISPLAYON);
  DEBUG_.print(F("Wakeup"));
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
void onBeforeSDReadWrite(const char* fileName, const __FlashStringHelper* message) {
  INTERRUPTS = false;
  sendMessage(fileName, message,0);
  AUDIO.stopPlaying();
  delay(10);
}
void onAfterSDReadWrite(const char* fileName, const __FlashStringHelper* message) {
  onAfterSDWork();
  sendMessage(fileName, message,MSG_DELAY);
  INTERRUPTS = true;
}
void onSDError(const char* fileName, const __FlashStringHelper* message) {
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

  STATE.dirNum = FILE_.dirNum;
  DEBUG_.print(F("SelectDir"),FILE_.dirNum,FILE_.path);    

}
void onAfterSelectFile(){

  STATE.fileNum = FILE_.fileNum;
  MARKERS_.selectArray();
  MP3.open(FILE_.path); MP3.close();  //Open and close to load bitrate & tags ID3v1
  if(!MP3.bitrate) MP3.bitrate = DFT_BITRATE;
  if(STATE.MODE == PLAYER){
    DISPLAY_.files.printPath(&FILE_, &MP3);
  }
  
  DEBUG_.print(F("SelectFile"),FILE_.fileNum,FILE_.path);  
  onAfterSDWork();


}

/**********************
* PLAYLISTS:
***********************/
void onPlayListSetPosition(uint8_t position[2]){
  STATE.playlistPosition[0] = position[0];
  STATE.playlistPosition[1] = position[1];
  DISPLAY_.playlists.nav(); 
  DISPLAY_.playlists.playList(); 
}
void onPlayListError(const char* label, const __FlashStringHelper* message){
  sendMessage(label, message,ERROR_MSG_DELAY);
}
void onPlayListConfirm(const char* label, const __FlashStringHelper* message){
  sendMessage(label, message,MSG_DELAY);
}
/**********************
* MARKERS:
***********************/
void onMarkerAdd(uint32_t position){
}
