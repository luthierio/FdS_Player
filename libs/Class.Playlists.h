#ifndef Playlists_H
#define Playlists_H


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
  char dirName[nameSize] = "/0";
  char fileName[nameSize] = "/0";
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

struct Playlist {
  PlaylistItem emptyItem;
  PlaylistItem *currentItem = &emptyItem;
  static const uint8_t size = NBR_PLAYLIST_ITEMS; 
  PlaylistItem items[NBR_PLAYLIST_ITEMS];
  uint8_t position = 0;

  PlaylistItem& getItem() { 
        return items[position];
  }
  PlaylistItem& getItem(int index) { 
      if (index >= 0 && index < size) {
        return items[index];
      }
      return emptyItem;
  }

  PlaylistItem& getCurrent() {
      return *currentItem; 
  }

  // Retourne la position
  uint8_t getPosition() {
    return position;
  }

  // Définit la position
  void setPosition(int index) {
    if (index >= 0 && index < size) {
      position = index;
      currentItem = &items[index]; 
    }
  }
  void clear(){
    for (uint8_t i = 0; i < size; ++i) {
      items[i].clear();
    }
  }
  bool isEmpty(){    
    for (uint8_t i = 0; i < size; ++i) {
      if(!items[i].isEmpty()){
        return false;
      }
    }
    return true;
  }
};

class PlaylistManager {
private:
  static const uint8_t nameSize = 18;
  uint8_t position[2] = {0, 0}; // Position de navigation
  // Tableau de références de playlists

  Playlist* playlists;
  
public:
  Playlist emptyPlaylist;
  Playlist *currentPlaylist = &emptyPlaylist;
  const uint8_t size = NBR_PLAYLISTS; 

  uint8_t playlistPosition = 0; 
  // Define event function pointers
  void (*onSetPosition)(uint8_t position) = nullptr;
  void (*onSetPlayPosition)(uint8_t position) = nullptr;
  void (*onError)(const char *label, const __FlashStringHelper *message) = nullptr; 
  void (*onConfirm)(const char *label, const __FlashStringHelper *message) = nullptr;

  PlaylistManager(Playlist* playlists, size_t size) : playlists(playlists), size(size) {}

  // Set callback functions
  void setCallbacks(
                    void (*onConfirmCallback)(const char *, const __FlashStringHelper *),
                    void (*onErrorCallback)(const char *, const __FlashStringHelper *),
                    void (*setPositionCallback)(uint8_t),
                    void (*setPlayPositionCallback)(uint8_t) 
                  ){
    onConfirm = onConfirmCallback; // Définir le callback pour la confirmation
    onError = onErrorCallback;     // Définir le callback pour les erreurs
    onSetPosition = setPositionCallback;
    onSetPlayPosition = setPlayPositionCallback;
  }

  Playlist& getPlaylist(int index) {
    if (index >= 0 && index < size) {
      return playlists[index]; 
    }
    return emptyPlaylist;
  }

  // Définit la position dans la playlist
  void setPlaylistPosition(uint8_t index[2], bool silent = false) {
    setPosition(index[0],silent);
    setPlayPosition(index[1],silent);
  }
  // Définit la playlist
  void setPosition(uint8_t index, bool silent = false) { 
    if (0 <= index && index < size) {
      playlistPosition = index; 
      currentPlaylist = &playlists[playlistPosition]; 
      if (!silent && onSetPosition != nullptr) {
        onSetPosition(index);
      }
    }
  }

  // Retourne la position de la playlist
  uint8_t getPosition() {
    return playlistPosition; 
  }

  // Retourne la position dans la playlist
  uint8_t getPlayPosition() {
    return currentPlaylist->getPosition();
  }

  bool currentPositionIsEmpty() {
    return currentPlaylist->getCurrent().isEmpty();
  }

  // Définit la position dans la playlist
  void setPlayPosition(uint8_t index, bool silent = false) {
    currentPlaylist->setPosition(index);
    if (!silent && onSetPosition != nullptr) {
        onSetPlayPosition(index);
    }
  }
  uint8_t getNextFreePosition(){
    for (uint8_t p = 0; p < currentPlaylist->size; ++p) {
      currentPlaylist->setPosition(p);
      if(currentPlaylist->currentItem->isEmpty()){
        return p;
      }      
    }
    onError(NULL, F("Playlist FULL"));
    return currentPlaylist->size-1;
  }
  // Sauve le fichier du filePicker dans la position
  void addCurrentFile(FilePicker *filePicker) {
    uint8_t freePosition = getNextFreePosition();
    currentPlaylist->setPosition(freePosition);
    addCurrentFileToCurrentPosition(filePicker);
  }
  // Sauve le fichier du filePicker dans la position
  void addCurrentFileToCurrentPosition(FilePicker *filePicker) {
    if (filePicker->exist()) {
      currentPlaylist->getCurrent().dirNum = filePicker->dirNum;
      currentPlaylist->getCurrent().fileNum = filePicker->fileNum;
      strncpy(currentPlaylist->getCurrent().dirName, filePicker->dirname + 3, nameSize);
      strncpy(currentPlaylist->getCurrent().fileName, filePicker->filename, nameSize);
    }
  }
  // charge une playlist m3u depuis la carte SD
  void loadM3U(FilePicker *filePicker) {

    for (uint8_t i = 0; i < size; ++i) {

      File file = filePicker->getByNum(filePicker->SD->open("/"), i, FILE_ONLY, ".m3u");

      if (!file) {
        continue;
      }

      char line[560]; 
      size_t n;
      uint8_t playPosition = 0;

      setPosition(i); 
      currentPlaylist->clear();
      while ((n = file.fgets(line, sizeof(line))) > 0) {

        if (line[0] != '#') {

          if (playPosition < currentPlaylist->size) {

            int8_t dirNum = -1;
            int8_t fileNum = -1;

            if (filePicker->getNumsFromPath(line, dirNum, fileNum)) {

              filePicker->select(dirNum, fileNum);

              if (filePicker->exist()) {

                currentPlaylist->setPosition(playPosition);
                addCurrentFile(filePicker);
                playPosition++;
                continue;

              } else if (onError != nullptr) {
                onError(NULL, F("Reference doen't exist"));
              }
            }

          } else {

            if (onError != nullptr) {
              onError(NULL, F("Max items reached"));
            }
            break;
          }
        }
      }
      file.close();
    }
    // On réinitialise les positions
    setPosition(0); 
    setPlayPosition(0);
    onConfirm(NULL, F("Loading M3U OK!"));
  }
  // charge une playlist m3u depuis la carte SD
  void saveM3U(FilePicker *filePicker) {

    for (uint8_t i = 0; i < size; ++i) {
      
      setPosition(i); 
      currentPlaylist->setPosition(0);
      if (currentPlaylist->isEmpty()){
        // On s'arrete la pour celle ci
        continue;
      }

      char prefix[3]; // Ajout d'un élément pour le caractère nul '\0'
      snprintf(prefix, sizeof(prefix), "%02d", i);
    

      File existingfile = filePicker->getByNum(filePicker->SD->open("/"), i, FILE_ONLY, ".m3u");

      char filename[250];
      if (!existingfile) {
        strcpy (filename,prefix);
        strcat (filename," ");
        strcat (filename,"playlist.m3u");  
        //onError(filename, F("Impossible de créer le fichier"));  
      }else{
        existingfile.getName(filename, sizeof(filename));
      }
      File file = filePicker->SD->open(filename, O_RDWR | O_CREAT | O_TRUNC);
      file.println("#EXTM3U");

      for (uint8_t p = 0; p < currentPlaylist->size; ++p) {
        currentPlaylist->setPosition(p);
        if(!currentPlaylist->currentItem->isEmpty()){
          filePicker->select(currentPlaylist->currentItem->dirNum, currentPlaylist->currentItem->fileNum);

          file.print("#EXTINF:-1,");
          file.println(filePicker->path);

          file.println(urlEncode(filePicker->path));
          file.println("");// ligne vide
        }
      }

      file.close();
    }
    // On réinitialise les positions
    setPosition(0); 
    setPlayPosition(0);
    onConfirm(NULL, F("SAving M3U OK!"));    
  }
};

#endif
