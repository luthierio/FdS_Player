
/**********************
* ACTIONS
***********************/
  
void doAction(int ID){ 
  DEBUG_.print("ACTION ", ID);
  
  SLEEP_WATCH.wakeUp();
  AUDIO.stopPlaying();
  
  switch (ID) {
    case ACCORD:
      // statements
      AUDIO.playFullFile(ACCORDAGE);    
      break;  
    case SAVE_ALL:
      // Save playlists
      SD_BACKUP.save(MARKERS_FILENAME, &DATAS, sizeof(DATAS));
      SD_BACKUP.save(STATE_FILENAME, &STATE, sizeof(STATE));
      //SD_BACKUP.save(sizeof(playLists),&playLists,PLAYLISTS_FILENAME);
      break;
    case LOAD_ALL:
      // Save playlists
      SD_BACKUP.load(MARKERS_FILENAME, &DATAS, sizeof(DATAS));
      SD_BACKUP.load(STATE_FILENAME, &STATE, sizeof(STATE));
      //SD_BACKUP.load(sizeof(playLists),&playLists,PLAYLISTS_FILENAME);
      // updateState(true);
      break;
    case MAR_SAVE:
      // Save markers
      SD_BACKUP.save(MARKERS_FILENAME, &DATAS, sizeof(DATAS));
      break;
    case MAR_LOAD:
      // load 
      SD_BACKUP.load(MARKERS_FILENAME, &DATAS, sizeof(DATAS));
      break;
    case ST_SAVE:
      // Save state
      SD_BACKUP.save(STATE_FILENAME, &STATE, sizeof(STATE));
      break;
    case ST_LOAD:
      // Load state
      SD_BACKUP.load(STATE_FILENAME, &STATE, sizeof(STATE));
      // updateState(true);
      break;
    case PL_SAVE:
      // Save playlists
      //SD_BACKUP.save(sizeof(playLists),&playLists,PLAYLISTS_FILENAME);
      break;
    case PL_LOAD:
      // Load playlists
      //SD_BACKUP.load(sizeof(playLists),&playLists,PLAYLISTS_FILENAME);
      break;
    case PL_EXPOR:
      // export m3u
      // actionResult = exportPlaylists();
      break;
    case DEBUG_ON:
      SERIAL_ON = !SERIAL_ON;
      if(SERIAL_ON){
        DEBUG_.setSerial(true);
      }else{
        DEBUG_.setSerial(false);
      }
      DEBUG_.print(F("SERIAL_ON"),SERIAL_ON);
      break;
    default:
      // statements
      break;
  }

}

