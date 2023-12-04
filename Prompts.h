
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
      SD_FS.save(PLAYLISTS_FILENAME, &PLAYLISTS, sizeof(PLAYLISTS));
      break;
    case PL_IMPORT:
      PLAYLISTS_.loadM3U(&FILE_);
      break;
    case PL_EXPORT:
      PLAYLISTS_.saveM3U(&FILE_);
      break;
    /*  
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

