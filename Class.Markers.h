#ifndef Markers_h   // Vérifie si MACLASSE_H n'a pas été défini
#define Markers_h   // Définit MACLASSE_H pour éviter les inclusions multiples
  
  #ifndef NBR_MARKERS
  #define NBR_MARKERS 20 // Nombre de playlists
  #endif

  #ifndef NBR_MARKER_ARRAYS
  #define NBR_MARKER_ARRAYS 100 // Nombre de références par playlist
  #endif

  struct markerArray {
      int8_t dirNum = -1;
      int8_t fileNum = -1;
      Array<uint32_t, NBR_MARKERS> markers;
      void clear() {
          // Remettez vos membres de structure à leurs valeurs par défaut ici
          dirNum = -1;
          fileNum = -1;
          markers.clean(); // Assurez-vous que la classe Array a une méthode clean() ou équivalente
      }
      bool isEmpty() const {
          return (dirNum == -1);
      }
  };

  class MarkersManager {
    private:
      markerArray (*markerArrays)[NBR_MARKERS];
    public:
      static const uint8_t nbr = NBR_MARKER_ARRAYS;
      static const uint8_t size = NBR_MARKERS;
      FilePicker *filePicker;
      // Define event function pointers
      void (*onSetPosition)(uint8_t position[2]) = nullptr;

      MarkersManager(FilePicker *filePicker, markerArray (*markerArrays)[NBR_MARKERS]) : filePicker(filePicker), markerArrays(markerArrays) {}

      // Set callback functions
      void setCallbacks(void (*setPositionCallback)(uint8_t[2])) {
          onSetPosition = setPositionCallback;
      }
      void addMarker(uint32_t position) {
        markerArray *array = getAvailableArray();
        if(array->isEmpty()){
          array->dirNum = filePicker->dirNum;
          array->fileNum = filePicker->fileNum;        
          array->markers.push(position);
        }
      }

      void deletePrevious(uint32_t position) {
        markerArray *array = getAvailableArray();
        array->markers.popPrevious(position);
      }

      void getPrevious( uint32_t position) {
        markerArray *array = getAvailableArray();
        array->markers.getPreviousFrom(position);
      }

      markerArray *getAvailableArray() {
        if (filePicker->exist()) {
          // Si il existe et n'est pas vide, on l'utilise
          for (byte i = 0; i < NBR_MARKER_ARRAYS; i = i + 1) {
              if (filePicker->dirNum == markerArrays[i]->dirNum && markerArrays[i]->fileNum == filePicker->fileNum) {
                  return markerArrays[i];
              }
          }

          // Sinon on prend le prochain espace vide comme référence
          for (byte i = 0; i < NBR_MARKER_ARRAYS; i = i + 1) {
              if (markerArrays[i]->markers.isEmpty()) {            
                  return markerArrays[i];
              }
          }

        }
        return nullptr;
      }
  };




  struct t_fileData {
      uint8_t dirNum;
      uint8_t fileNum;
      Array<uint32_t, NBR_MARKERS> markers;
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
  t_fileData DATAS[NBR_MARKER_ARRAYS];
  t_fileData emptyData;
  t_fileData *DATA = &DATAS[0];

  t_fileData &getFileDataRef(int dirNum, int fileNum) {
      // Si il existe et n'est pas vide, on l'utilise
      for (byte i = 0; i < NBR_MARKER_ARRAYS; i = i + 1) {
          if (dirNum == DATAS[i].dirNum && DATAS[i].fileNum == fileNum) {
              return DATAS[i];
          }
      }

      // Sinon on prend le prochain espace vide comme référence
      for (byte i = 0; i < NBR_MARKER_ARRAYS; i = i + 1) {
          if (DATAS[i].markers.isEmpty()) {            
              return DATAS[i];
          }
      }

      // Si on a rien trouvé de disponible, on envoie un tableau qui se vide et ne se sauve pas
      // Il faudra avertir l'utilisateur sur l'écran
      emptyData.clear();
      return emptyData;
  }



#endif