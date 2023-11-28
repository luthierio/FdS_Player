#ifndef Playlists_H
#define Playlists_H

#include <Arduino.h>

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

struct Playlist {
  PlaylistItem emptyItem;
  PlaylistItem *currentItem = &emptyItem;
  static const uint8_t size = NBR_PLAYLIST_ITEMS; // Corrected size to NBR_PLAYLISTS
  PlaylistItem items[NBR_PLAYLIST_ITEMS];
  uint8_t position = 0;

  PlaylistItem& getItem() { 
        return items[position];
  }
  PlaylistItem& getItem(int index) { // Corrected function name from getItems to getItem
      if (index >= 0 && index < size) {
        return items[index];
      }
      return emptyItem;
  }

  PlaylistItem& getCurrent() {
      return *currentItem; // Corrected variable name from current to currentItem
  }

  // Retourne la position
  uint8_t getPosition() {
    return position;
  }

  // Définit la position
  void setPosition(int index) {
    if (index >= 0 && index < size) {
      position = index;
      currentItem = &items[index]; // Corrected variable name from current to currentItem
    }
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
  static const uint8_t size = NBR_PLAYLISTS; // Corrected size to NBR_PLAYLISTS

  uint8_t playlistPosition = 0; // Corrected variable name from position to playlistPosition
  // Define event function pointers
  void (*onSetPosition)(uint8_t position) = nullptr;
  void (*onSetPlayPosition)(uint8_t position) = nullptr;
  void (*onError)(const char *label, const __FlashStringHelper *message) = nullptr; // Nouveau callback pour les erreurs
  void (*onConfirm)(const char *label, const __FlashStringHelper *message) = nullptr; // Nouveau callback pour les erreurs

  PlaylistManager(Playlist* playlists, size_t size) : playlists(playlists) {}

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
      return playlists[index]; // Corrected variable name from Playlist to playlists
    }
    return emptyPlaylist;
  }

  // Définit la position dans la playlist
  void setPlaylistPosition(uint8_t index[2], bool silent = false) {
    setPosition(index[0],silent);
    setPlayPosition(index[1],silent);
  }
  // Définit la playlist
  void setPosition(uint8_t index, bool silent = false) { // Corrected function name from setPosition to setPlaylistPosition
    if (0 <= index && index < size) {
      playlistPosition = index; // Corrected variable name from position to playlistPosition
      currentPlaylist = &playlists[playlistPosition]; // Corrected variable name from Playlist to playlists
      if (!silent && onSetPosition != nullptr) {
        onSetPosition(index);
      }
    }
  }

  // Retourne la position de la playlist
  uint8_t getPosition() {
    return playlistPosition; // Corrected variable name from position to playlistPosition
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

  // Sauve le fichier du filePicker dans la position
  void addCurrentFile(FilePicker *filePicker) {
    if (filePicker->exist()) {
      currentPlaylist->getCurrent().dirNum = filePicker->dirNum;
      currentPlaylist->getCurrent().fileNum = filePicker->fileNum;
      strncpy(currentPlaylist->getCurrent().dirName, filePicker->dirname + 3, nameSize);
      strncpy(currentPlaylist->getCurrent().fileName, filePicker->filename, nameSize);
    }
  }
  // Sauve le fichier du filePicker dans la position
  void loadM3U(FilePicker *filePicker) {

    for (uint8_t i = 0; i < size; ++i) {

      File file = filePicker->getByNum(filePicker->SD->open("/"), i, FILE_ONLY, ".m3u");

      if (!file) {
        continue;
      }

      char line[560]; // Maximum line length plus space for zero byte.
      size_t n;
      uint8_t playPosition = 0;

      setPosition(i); // Corrected function name from setPosition to setPlaylistPosition

      while ((n = file.fgets(line, sizeof(line))) > 0) {

        if (line[0] != '#') {

          if (playPosition < currentPlaylist->size) {

            int8_t dirNum = -1;
            int8_t fileNum = -1;

            if (filePicker->getNumsFromPath(line, dirNum, fileNum)) {

              filePicker->select(dirNum, fileNum);

              if (filePicker->exist()) {

                currentPlaylist->setPosition(playPosition); // Corrected function name from setPosition to setPlayPosition
                addCurrentFile(filePicker);
                playPosition++;
                continue;

              } else if (onError != nullptr) {
                onError(NULL, F("La référence n'existe pas"));
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
    setPosition(0); // Corrected function name from setPosition to setPlaylistPosition
    setPlayPosition(0);
    onConfirm(NULL, F("M3U Chargement OK!"));
  }
};

#endif
