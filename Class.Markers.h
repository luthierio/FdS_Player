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

      bool isEmpty() {
        markerArray *array = getFileArray();
        return array->isEmpty();        
      }
      uint32_t *getMarkers() {
        markerArray *array = getFileArray();
        return array->markers.get();        
      }

      void addMarker(uint32_t position) {
        markerArray *array = getFileArray();
        if(array->isEmpty()){
          array->dirNum = filePicker->dirNum;
          array->fileNum = filePicker->fileNum;        
          array->markers.push(position);
        }
      }

      void deletePrevious(uint32_t position) {
        markerArray *array = getFileArray();
        array->markers.popPrevious(position);
      }

      uint32_t getPrevious( uint32_t position) {
        markerArray *array = getFileArray();
        return array->markers.getPreviousFrom(position);
      }

      markerArray *getFileArray() {
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

#endif