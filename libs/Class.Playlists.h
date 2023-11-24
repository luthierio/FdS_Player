#ifndef Playlists_H   // Vérifie si MACLASSE_H n'a pas été défini
#define Playlists_H   // Définit MACLASSE_H pour éviter les inclusions multiples
  
  #ifndef NBR_PLAYLISTS
  #define NBR_PLAYLISTS 6 // Nombre de playlists
  #endif

  #ifndef NBR_PLAYLIST_ITEMS
  #define NBR_PLAYLIST_ITEMS 30 // Nombre de références par playlist
  #endif


  struct PlaylistItem {
      int8_t dirNum = -1;
      int8_t fileNum = -1;
      static const uint8_t nameSize = 18;
      char dirName[nameSize] = {};
      char fileName[nameSize] = {};
      void clear() {
          dirNum = -1;
          fileNum = -1;
          memset(dirName, 0, nameSize);
          memset(fileName, 0, nameSize);
      }
      bool isEmpty() const {
          return (dirNum == -1);
      }
  };

  class PlaylistManager {
    private:
      static const uint8_t nameSize = 18;
      uint8_t position[2] = {0, 0};
      // Tableau de références de playlists
      PlaylistItem (*playlists)[NBR_PLAYLIST_ITEMS];

      // Tableau pour suivre le nombre d'éléments dans chaque playlist
      int playlistItemCount[NBR_PLAYLISTS] = {0};

    public:
      static const uint8_t nbr = NBR_PLAYLISTS;
      static const uint8_t size = NBR_PLAYLIST_ITEMS;
      // Define event function pointers
      void (*onSetPosition)(uint8_t position[2]) = nullptr;

      PlaylistManager(PlaylistItem (*playlists)[NBR_PLAYLIST_ITEMS]) : playlists(playlists) {}

      // Set callback functions
      void setCallbacks(void (*setPositionCallback)(uint8_t[2])) {
          onSetPosition = setPositionCallback;
      }

      // Retourne les deux curseurs de position
      uint8_t *getPosition() const {
          return position;
      }
      
      // Retourne les deux curseurs de position
      uint8_t getPlayPosition() {
          return position[1];
      }
      bool currentPositionIsEmpty(){   
          PlaylistItem *current = &playlists[position[0]][position[1]];  
          return current->isEmpty();
      }

      //Défini la playlist
      void setPosition(uint8_t index, bool silent = false) {
          if (0 <= index && index < NBR_PLAYLISTS) {
              position[0] = index;
              // Trigger the onSetPosition event
              if (!silent && onSetPosition != nullptr) {
                  onSetPosition(position);
              }
          }
      }

      //Défini la position dans la playlist
      void setPlayPosition(uint8_t index, bool silent = false) {
          if (0 <= index && index < NBR_PLAYLIST_ITEMS) {
              position[1] = index;
              // Trigger the onSetPlayPosition event
              if (!silent && onSetPosition != nullptr) {
                  onSetPosition(position);
              }
          }
      }

      //Défini les deux curseurs de position
      void setPosition(uint8_t index[2], bool silent = false) {
          if (0 <= index[0] < NBR_PLAYLISTS && 0 <= index[1] < NBR_PLAYLIST_ITEMS) {
              position[0] = index[0];
              position[1] = index[1];
              // Trigger the onSetPosition event
              if (!silent && onSetPosition != nullptr) {
                  onSetPosition(position);
              }
          }
      }

      //Sélection le fichier via FilePicker à partir de la position courante
      bool selectFile(FilePicker *filePicker) {
          PlaylistItem *current = &playlists[position[0]][position[1]];
          if (!current->isEmpty()) {
              if(current->dirNum == filePicker->dirNum && current->fileNum == filePicker->fileNum){
                //On est déja sur le bon fichier
                return true;
              }
              
              filePicker->select(current->dirNum, current->fileNum);
              // Ajoutez le reste de votre logique pour sélectionner le fichier
              if (filePicker->exist()) {
                return true;
              }
          }
          return false;
      }

      //Sauve le fichier du filePicker dans la position
      void addCurrentFile(FilePicker *filePicker) {
          PlaylistItem *current = &playlists[position[0]][position[1]];
          if (filePicker->exist()) {
              current->dirNum = filePicker->dirNum;
              current->fileNum = filePicker->fileNum;
              strncpy(current->dirName, filePicker->dirname + 3, nameSize);
              strncpy(current->fileName, filePicker->filename, nameSize);
          }
      }

      PlaylistItem *getItem() {
          return &playlists[position[0]][position[1]];
      }

      PlaylistItem *getItem(uint8_t index) {
          return &playlists[position[0]][index];
      }

      PlaylistItem *getPlaylist() {
          return &playlists[position[0]][0];
      }

      PlaylistItem *getPlaylist(uint8_t index) {
          if (0 <= index && index < NBR_PLAYLISTS) {
              return &playlists[index][0];
          } else {
              return nullptr;
          }
      }
  };

#endif
