#ifndef Markers_h   // Vérifie si MACLASSE_H n'a pas été défini
#define Markers_h   // Définit MACLASSE_H pour éviter les inclusions multiples
  
  #ifndef NBR_PLAYLISTS
  #define NBR_PLAYLISTS 6 // Nombre de playlists
  #endif

  #ifndef NBR_PLAYLIST_ITEMS
  #define NBR_PLAYLIST_ITEMS 30 // Nombre de références par playlist
  #endif

  struct t_fileData {
      uint8_t dirNum;
      uint8_t fileNum;
      Array<uint32_t, MAX_MARKERS> markers;
      void addMarker(FilePicker *FILE_, FdS_Adafruit_VS1053_FilePlayer *AUDIO) {
        this->dirNum = FILE_->dirNum;
        this->fileNum = FILE_->fileNum;
        markers.push(AUDIO->getFilePosition());
      }
      void clear() {
          // Remettez vos membres de structure à leurs valeurs par défaut ici
          dirNum = 0;
          fileNum = 0;
          markers.clean(); // Assurez-vous que la classe Array a une méthode clean() ou équivalente
      }
  };
  t_fileData DATAS[MAX_FILES_DATA];
  t_fileData emptyData;
  t_fileData *DATA = &DATAS[0];
#endif