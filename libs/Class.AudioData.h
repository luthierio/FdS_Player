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
      bool pitchDirection;
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
      audioData  emptyData;
      FilePicker *filePicker;
      size_t size;
      // Méthode pour accéder à une instance spécifique du tableau
      audioData& getInstance(int index) {
          if (index >= 0 && index < size) {
            return audioDatas[index];
          }
          Serial.println("index out of range");
          return emptyData;
      }
    public:
      audioData* active;
      // Define event function pointers
      void (*onAdd)(uint32_t position) = nullptr;
      void (*onSetPitch)(uint8_t step, bool direction) = nullptr;

      audioDataManager(FilePicker *filePicker, audioData* datas, size_t size) : filePicker(filePicker), audioDatas(datas), size(size) {}

      // Set callback functions
      void setCallbacks(
            void (*onAddCallback)(uint32_t),
            void (*onSetPichCallback)(uint8_t, bool)
          ) {
          onAdd = onAddCallback;
          onSetPitch = onSetPichCallback;
      }
      
      uint8_t getPitchStep(){
        return active->pitchStep;
      }

      uint8_t getPitchDirection(){
        return active->pitchDirection;
      }

      audioData *getActive(){
        return active;
      }

      void select(){
        active = getAvailableFileData();
      }

      void setPitchStep(uint8_t pitchStep){
        activate();
        active->pitchStep = pitchStep;
        if (onSetPitch != nullptr) {
            onSetPitch(active->pitchStep,active->pitchDirection);
        }
      }

      void setPitchDirection(bool direction){
        activate();
        active->pitchDirection = direction;
        if (onSetPitch != nullptr) {
            onSetPitch(active->pitchStep,active->pitchDirection);
        }
      }
      void switchPitchDirection(){
        setPitchDirection(!active->pitchDirection);
      }


      bool hasData() const {
          return (active != nullptr && !active->isUnset()) ? true : false;
      }
      bool markersIsEmpty() const {
          return (active == nullptr) ? true : active->markers.isEmpty();
      }

      uint32_t getMarkerCount() const {
          return (active == nullptr) ? 0 : active->markers.count;
      }

      uint32_t* getMarkers() {
          return (active == nullptr) ? nullptr : active->markers.get();
      }

      void addMarker(uint32_t position) {
          activate();

          active->markers.push(position);

          if (onAdd != nullptr) {
              onAdd(position);
          }
      }
      void activate() {
          active = getAvailableFileData();
          if (active != nullptr && active->isUnset()) {
              active->dirNum = filePicker->dirNum;
              active->fileNum = filePicker->fileNum;
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


      audioData *getAvailableFileData() {
        if (filePicker->exist()) {
          // Si il existe et n'est pas vide, on l'utilise
          for (byte i = 0; i < size; i = i + 1) {
              if (filePicker->dirNum == getInstance(i).dirNum && getInstance(i).fileNum == filePicker->fileNum) {
                  return &getInstance(i);
              }
          }

          // Sinon on prend le prochain espace vide comme référence
          for (byte i = 0; i < size; i = i + 1) {
              if (getInstance(i).isUnset()) {            
                  return &getInstance(i);
              }
          }

        }
        return nullptr;
      }
  };

#endif
