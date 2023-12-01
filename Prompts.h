
/**********************
* PROMPT_IDS
***********************/
  
void executePrompt(int ID){ 
  DEBUG_.print(F("PROMPT_ID "), ID);
  
  SLEEP_WATCH.wakeUp();
  AUDIO.stopPlaying();
  
  switch (ID) {
    case PL_ADD:
      PLAYLISTS_.addCurrentFile(&FILE_);
      break;
    case PL_IMPORT:
      PLAYLISTS_.loadM3U(&FILE_);
      break;
    case PL_EXPORT:
      PLAYLISTS_.saveM3U(&FILE_);
      break;
    /*
    case ACCORD:
      // statements
      AUDIO.playFullFile(ACCORDAGE);    
      break;  
    case SAVE_ALL:
      // Save playlists
      SD_FS.save(DATA_FILENAME, &DATAS, sizeof(DATAS));
      SD_FS.save(STATE_FILENAME, &STATE, sizeof(STATE));
      //SD_FS.save(sizeof(playLists),&playLists,PLAYLISTS_FILENAME);
      break;
    case LOAD_ALL:
      // Save playlists
      SD_FS.load(DATA_FILENAME, &DATAS, sizeof(DATAS));
      SD_FS.load(STATE_FILENAME, &STATE, sizeof(STATE));
      //SD_FS.load(sizeof(playLists),&playLists,PLAYLISTS_FILENAME);
      // updateState(true);
      break;
    case MAR_SAVE:
      // Save markers
      SD_FS.save(DATA_FILENAME, &DATAS, sizeof(DATAS));
      break;
    case MAR_LOAD:
      // load 
      SD_FS.load(DATA_FILENAME, &DATAS, sizeof(DATAS));
      break;
    case ST_SAVE:
      // Save state
      SD_FS.save(STATE_FILENAME, &STATE, sizeof(STATE));
      break;
    case ST_LOAD:
      // Load state
      SD_FS.load(STATE_FILENAME, &STATE, sizeof(STATE));
      // updateState(true);
      break;
    case PL_SAVE:
      // Save playlists
      //SD_FS.save(sizeof(playLists),&playLists,PLAYLISTS_FILENAME);
      break;
    case PL_LOAD:
      // Load playlists
      //SD_FS.load(sizeof(playLists),&playLists,PLAYLISTS_FILENAME);
      break;
    case PL_EXPOR:
      // export m3u
      // actionResult = exportPlaylists();
      break;
      
    case DEBUG_ON:
      SERIAL_ON = !SERIAL_ON;
      if(SERIAL_ON){
        DEBUG_.setEnabled(true);
      }else{
        DEBUG_.setEnabled(false);
      }
      DEBUG_.print(F("SERIAL_ON"),SERIAL_ON);
      break;
    */
    default:
      // statements
      break;
  }

}

