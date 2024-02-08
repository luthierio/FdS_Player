
/**********************
* AUDIO:
***********************/

void afterStartPlaying(){
  delay(50);
  PITCHER.setPitch(DATA_MANAGER.getPitchStep(), DATA_MANAGER.getPitchMode());
}
/**********************
* MODE:
***********************/
void refreshDisplay() {

  DISPLAY_.clear();
  
  if (STATE.MODE == PLAYER) {

      DISPLAY_.files.show(); 

  } else if (STATE.MODE == PROMPT) {

      DISPLAY_.menu.show(PROMPT_ID, CONFIRM); 

  } else if (STATE.MODE == PLAYLIST) {

      DISPLAY_.playlists.show(); 

  } else if (STATE.MODE == METRONOME) {

      DISPLAY_.metronome.show();

  } else if (STATE.MODE == LOGO) {

      DISPLAY_.display.logo();

  }
  //This function should receive all
  DISPLAY_.show();

}
void setMode(uint8_t mode) {
  
  DEBUG_.print(F("MODE"), mode);
  STATE.MODE = mode;

  if (STATE.MODE == PLAYER) {

      R_DIR->setUpperBound(MAX_DIR_NUM);
      R_DIR->resetPosition(FILE_.dirNum, false);
      R_FILES->setUpperBound(MAX_FILES_NUM);
      R_FILES->resetPosition(FILE_.fileNum, false);
      R_DIR->setCanLoop(true);
      R_FILES->setCanLoop(true);

      R_PITCH->resetPosition(DATA_MANAGER.getPitchStep(), false);
  
  } else if (STATE.MODE == PLAYLIST) {

      R_DIR->setUpperBound(NBR_PLAYLISTS-1);
      R_DIR->resetPosition(PLAYLISTS_.getPosition(), false);
      R_FILES->setUpperBound(NBR_PLAYLIST_ITEMS-1);
      R_FILES->resetPosition(PLAYLISTS_.getPlayPosition(), false);
      R_DIR->setCanLoop(false);
      R_FILES->setCanLoop(false);
      R_PITCH->resetPosition(DATA_MANAGER.getPitchStep(), false);

  } else if (STATE.MODE == METRONOME) {

      R_DIR->setLowerBound(MIN_BEATS);
      R_DIR->setUpperBound(MAX_BEATS);
      R_DIR->setCanLoop(false);
      R_DIR->resetPosition(METRONOME_.getBeatsPerBar(), false);

      R_FILES->setLowerBound(MIN_BPM);
      R_FILES->setUpperBound(MAX_BPM);
      R_FILES->setCanLoop(false);
      R_FILES->resetPosition(METRONOME_.getBpm(), false);


  } else if (STATE.MODE == PROMPT) {
      R_FILES->setLowerBound(0);
      R_FILES->setUpperBound(1);
      R_DIR->resetPosition(CONFIRM);
      R_FILES->setCanLoop(true);
  }
  refreshDisplay();
}
//Define action and context
void setPrompt(uint8_t promptID, uint8_t context) {
  PROMPT_ID = promptID;
  CONTEXT = context;
  setMode(PROMPT);
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
      if(&rotary == R_PITCH ) {
        DATA_MANAGER.setPitchStep(currentPosition);
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
  * METRONOME:
  ***********************/
  } else if (STATE.MODE == METRONOME) {       
      if(&rotary == R_DIR) {
        METRONOME_.setBeatsPerBar(currentPosition);
      }  
      if(&rotary == R_FILES) {
        METRONOME_.setBpm(currentPosition);
      }

  /**********************
  * PROMPT:
  ***********************/
  } else if (STATE.MODE == PROMPT) {
    CONFIRM = !CONFIRM;
    DISPLAY_.menu.show(PROMPT_ID, CONFIRM); 
  }  
}

void onRotUpLimit(Rotary &rotary) {
}
void onRotLowLimit(Rotary &rotary) {  
}

/**********************
* BUTTONS:
***********************/
bool CONTINUE; // A chaque action, pour tester si l'on doit continuer a agir
void onPress(ButtonHandler* buttonHandler, int ID) {

  CONTINUE = true;
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

          if(DATA_MANAGER.markersIsEmpty()){

            uint32_t jump = MP3.getBytePerSecond()*SECONDS_PER_JUMP;
            JumpPosition = AUDIO.getFilePosition() - jump > 0? AUDIO.getFilePosition() - jump : 0;  

          }else{
            //on cherche 1 seconde en arrière pour sauter au précédent si on est très proche du marker
            JumpPosition =DATA_MANAGER.getPrevious(AUDIO.getFilePosition()- MP3.getBytePerSecond()); 
          } 
          AUDIO.jumpTo(JumpPosition);
          break;

        case 3:
          //Got to playlist on release
          break;

        case 4:
          if(STATE.playMode < REPEATONE){STATE.playMode++;}        
          else{STATE.playMode = ONEPLAY;}
          break;

        case 5:
          //Switch mode on release
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
          setPrompt(PL_ADD, PLAYLIST);
          break;

        case 3:
          break;

        case 4:
          if(STATE.playlistMode < REPEATONE){STATE.playlistMode++;}        
          else{STATE.playlistMode = ONEPLAY;}
          DISPLAY_.playlists.printList(); 
          break;

        case 5:
          //Add selected file on Release
          break;

        default:
          break;
      }

  /**********************
  * METRONOME:
  ***********************/
  } else if (STATE.MODE == METRONOME) {
      METRONOME_.switchOnOff();
      //setMode(PLAYER);

  /**********************
  * PROMPT_ID:
  ***********************/
  } else if (STATE.MODE == PROMPT) {

    if(ID == 5 && CONTEXT == PLAYLIST){

      if       (PROMPT_ID == PL_IMPORT){
        setPrompt(PL_EXPORT, PLAYLIST);
      }else {
        setPrompt(PL_IMPORT, PLAYLIST);
      }
      CONTINUE = false;

    }else{

      //Tout les boutons lancent l'action si nécessaire puis retournent au contexte
      if(CONFIRM){
        executePrompt(PROMPT_ID);
      }
      setMode(CONTEXT);
      CONTINUE = false;

    }

  }

  DEBUG_.print(F("Pressed"), ID);
  delay(10);
}
void onLongPress(ButtonHandler* buttonHandler, int ID) {

  if (CONTINUE) {

    /**********************
    * PLAYER:
    ***********************/
    if (STATE.MODE == PLAYER) {

        // Long press
        switch (ID) {

          case 0:
            SD_FS.save(DATA_FILENAME, &DATAS, sizeof(DATAS));
            SD_FS.save(STATE_FILENAME, &STATE, sizeof(STATE));
            refreshDisplay();
            break;

          case 1:
            //On vérifie que le fichier Sélectionné est bien celui qui joue pour ajouter un marqueur
            if(AUDIO.getFilePosition() && AUDIO.currentTrack.size() == FILE_.getSize()){
              DATA_MANAGER.addMarker(AUDIO.getFilePosition());

              DEBUG_.print(F("New marker"), (int)DATA_MANAGER.getMarkerCount());
              
              AUDIO.pausePlaying(false);
            }
            break;

          case 2:
            if(AUDIO.getFilePosition() && AUDIO.currentTrack.size() == FILE_.getSize()){
              DATA_MANAGER.deletePrevious(AUDIO.getFilePosition());
            }
            break;

          case 3:
            setPrompt(PL_ADD, PLAYER);
            CONTINUE = false;
            break;

          case 5:
            setMode(METRONOME);
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
            setPrompt(PL_IMPORT, PLAYLIST);
            CONTINUE = false;
            
            break;
          default:
            break;
        }

    /**********************
    * METRONOME:
    ***********************/
    } else if (STATE.MODE == METRONOME) {
        METRONOME_.switchOff();
        setMode(PLAYER);
    } 
    
    DEBUG_.print(F("LongPress"), ID);
  
  }  
}


void onRelease(ButtonHandler* buttonHandler, int ID) {

  if (CONTINUE) {

    /**********************
    * PLAYER:
    ***********************/
    if (STATE.MODE == PLAYER) {
      switch (ID) {
        case 0:
          AUDIO.stopPlaying();
          DEBUG_.print(F("Playing"), FILE_.path);
          AUDIO.startPlayingFile(FILE_.path);
          afterStartPlaying();
          break;
        case 3:
          setMode(PLAYLIST);
          break;
        case 5:
          DATA_MANAGER.switchPitchMode();
          DATA_MANAGER.setPitchStep(DFT_PITCH_STEP);
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
            FILE_.select(PLAYLISTS_.currentPlaylist->currentItem->dirNum, PLAYLISTS_.currentPlaylist->currentItem->fileNum);
            AUDIO.startPlayingFile(FILE_.path);
            afterStartPlaying();
          }
          break;
        case 3:
          setMode(PLAYER);
          break;
        case 5:
          //Add selected file on Release
          PLAYLISTS_.addCurrentFileToCurrentPosition(&FILE_);
          //refreshDisplay();
          DISPLAY_.playlists.printList(); 
        default:
          break;
      }

    }
    DEBUG_.print(F("Release"), ID);

  }
}
void onLongRelease(ButtonHandler* buttonHandler, int ID) {
  if (CONTINUE) {
    DEBUG_.print(F("LongRelease"), ID);
  }
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
        afterStartPlaying();
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
          FILE_.select(PLAYLISTS_.currentPlaylist->currentItem->dirNum, PLAYLISTS_.currentPlaylist->currentItem->fileNum);
          AUDIO.startPlayingFile(FILE_.path); 
          afterStartPlaying();
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
* MULTICLASS ERRORS:
***********************/
void onError(const char* fileName, const __FlashStringHelper* message) {
  sendMessage(fileName, message,ERROR_MSG_DELAY);
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



void onBeforeSelectDir(){
  onBeforeSDWork();
}
void onBeforeSelectFile(){
  onBeforeSDWork();
}
void onAfterSelectDir(){

  STATE.dirNum = FILE_.dirNum;
  DEBUG_.print(F("SelectDir"),FILE_.dirNum,FILE_.path);    
  onAfterSDWork();

}
void onAfterSelectFile(){

  STATE.fileNum = FILE_.fileNum;
  DATA_MANAGER.select();
  //MP3.open(FILE_.path); MP3.close();  //Open and close to load bitrate & tags ID3v1
  MP3_MUST_LOAD = true; //Prochaine boucle on charge les MP3

  if(STATE.MODE == PLAYER){
    DISPLAY_.files.printPath();
  }
  
  DEBUG_.print(F("SelectFile"),FILE_.fileNum,FILE_.path);  
  onAfterSDWork();
}
void onMp3Load(){  

  MP3.open(FILE_.path); MP3.close();
  if(!MP3.bitrate) MP3.bitrate = DFT_BITRATE;
  if(STATE.MODE == PLAYER){
    DISPLAY_.files.printPath();
  }
    
  if(STATE.MODE == PLAYER){
    DISPLAY_.files.printPath();
  }
}
/**********************
* DATAS:
***********************/
void onAddFileMarker(uint32_t position){
}
void onSetFilePitch(uint8_t step, bool speed){

  if(FILE_.isPlaying(&AUDIO) ) {
    PITCHER.setPitch(DATA_MANAGER.getPitchStep(), DATA_MANAGER.getPitchMode());
  }
  DISPLAY_.playing.pitch(105 , 52 , 10 , 10 );     

}

/**********************
* PLAYLISTS:
***********************/
void onPlayListPositionUpdate(){
  DISPLAY_.playlists.printNav(); 
  DISPLAY_.playlists.printList(); 
}
void onPlayListSetPosition(uint8_t position){
  STATE.playlistPosition[0] = position;
  onPlayListPositionUpdate();
}
void onPlayListSetPlayPosition(uint8_t position){
  STATE.playlistPosition[1] = position;
  onPlayListPositionUpdate();
}
void onPlayListError(const char* label, const __FlashStringHelper* message){
  sendMessage(label, message,ERROR_MSG_DELAY);
}
void onPlayListConfirm(const char* label, const __FlashStringHelper* message){
  sendMessage(label, message,MSG_DELAY);
}
/**********************
* METRONOME:
***********************/
void onBeat(){  
  SLEEP_WATCH.keepAlive();
}
