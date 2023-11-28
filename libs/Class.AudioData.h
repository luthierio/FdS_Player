#ifndef Markers_h   // Vérifie si MACLASSE_H n'a pas été défini
#define Markers_h   // Définit MACLASSE_H pour éviter les inclusions multiples
  
  #ifndef NBR_MARKERS
    #define NBR_MARKERS 10 // Nombre de playlists
  #endif

  #ifndef NBR_AUDIO_DATA
    #define NBR_AUDIO_DATA 100 // Nombre de références par playlist
  #endif

  struct audioData {
      int8_t dirNum = -1;
      int8_t fileNum = -1;
      uint8_t pitchStep = 5;
      uint8_t pitchMode = OFF;
      Array<uint32_t, NBR_MARKERS> markers;
      void clear() {
          // Remettez vos membres de structure à leurs valeurs par défaut ici
          dirNum = -1;
          fileNum = -1;
          markers.clean(); // Assurez-vous que la classe Array a une méthode clean() ou équivalente
      }
      bool isUnset() const {
          return (dirNum == -1);
      }
  };

  class audioDataManager {
    private:
      audioData* audioDatas;
      audioData* active;
      audioData  emptyData;
      size_t size;
      // Méthode pour accéder à une instance spécifique du tableau
      audioData& getInstance(int index) {
          if (index >= 0 && index < size) {
            return audioDatas[index];
          }
          return emptyData;
      }
    public:
      FilePicker *filePicker;
      // Define event function pointers
      void (*onAdd)(uint32_t position) = nullptr;

      audioDataManager(FilePicker *filePicker, audioData* data, size_t size) : filePicker(filePicker), audioDatas(data), size(size) {}

      // Set callback functions
      void setCallbacks(void (*onAddCallback)(uint32_t)) {
          onAdd = onAddCallback;
      }
      
      void select(){
        active = getFileData();
      }


      bool isEmpty() const {
          return (active == nullptr) ? true : active->markers.isEmpty();
      }

      uint32_t getCount() const {
          return (active == nullptr) ? 0 : active->markers.count;
      }

      uint32_t* getMarkers() {
          return (active == nullptr) ? nullptr : active->markers.get();
      }

      void addMarker(uint32_t position) {
          if (active == nullptr || active->isUnset()) {
              active = getFileData();
              if (active == nullptr) {
                  // Gérer le cas où il n'y a plus d'espace pour les références de fichiers
                  return;
              }
              active->dirNum = filePicker->dirNum;
              active->fileNum = filePicker->fileNum;
          }

          active->markers.push(position);

          if (onAdd != nullptr) {
              onAdd(position);
          }
      }
      
      void deletePrevious(uint32_t position) {
          if (active != nullptr) {
              active->markers.popPrevious(position);
          }
      }

      uint32_t getPrevious(uint32_t position) const {
          return (active == nullptr) ? 0 : active->markers.getPreviousFrom(position);
      }


      audioData *getFileData() {
        if (filePicker->exist()) {
          // Si il existe et n'est pas vide, on l'utilise
          for (byte i = 0; i < size; i = i + 1) {
              if (filePicker->dirNum == getInstance(i).dirNum && getInstance(i).fileNum == filePicker->fileNum) {
                  return &getInstance(i);
              }
          }

          // Sinon on prend le prochain espace vide comme référence
          for (byte i = 0; i < size; i = i + 1) {
              if (getInstance(i).markers.isEmpty()) {            
                  return &getInstance(i);
              }
          }

        }
        return nullptr;
      }
  };

#endif
