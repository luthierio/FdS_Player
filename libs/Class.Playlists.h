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

class PlaylistManager {
private:
  static const uint8_t nameSize = 18;
  uint8_t position[2] = {0, 0}; // Position de navigation
  // Tableau de références de playlists
  PlaylistItem (*playlists)[NBR_PLAYLIST_ITEMS];
  // Tableau pour suivre le nombre d'éléments dans chaque playlist
  int playlistItemCount[NBR_PLAYLISTS] = {0};

  // Définit la playlist
  void updateCurrentItem() {
    if (0 <= position[0] < NBR_PLAYLISTS && 0 <= position[1] < NBR_PLAYLIST_ITEMS) {
      current = &playlists[position[0]][position[1]];
    } else {
      current = &emptyItem;
      if (onError != nullptr) {
        onError(NULL, F("wrong position"));
      }
    }
  }

public:
  PlaylistItem emptyItem;
  PlaylistItem *current = &emptyItem;
  static const uint8_t nbr = NBR_PLAYLISTS;
  static const uint8_t size = NBR_PLAYLIST_ITEMS;
  // Define event function pointers
  void (*onSetPosition)(uint8_t position[2]) = nullptr;
  void (*onError)(const char *label, const __FlashStringHelper *message) = nullptr; // Nouveau callback pour les erreurs
  void (*onConfirm)(const char *label, const __FlashStringHelper *message) = nullptr; // Nouveau callback pour les erreurs

  PlaylistManager(PlaylistItem (*playlists)[NBR_PLAYLIST_ITEMS]) : playlists(playlists) {}

  // Set callback functions
  void setCallbacks(void (*onConfirmCallback)(const char *, const __FlashStringHelper *),
                    void (*onErrorCallback)(const char *, const __FlashStringHelper *),
                    void (*setPositionCallback)(uint8_t[2])) {
    onConfirm = onConfirmCallback; // Définir le callback pour la confirmation
    onError = onErrorCallback;     // Définir le callback pour les erreurs
    onSetPosition = setPositionCallback;
  }

  // Retourne les deux curseurs de position
  uint8_t getPlayListPosition() {
    return position[0];
  }
  // Retourne les deux curseurs de position
  uint8_t getPlayPosition() {
    return position[1];
  }

  bool currentPositionIsEmpty() {
    return current->isEmpty();
  }

  // Définit la playlist
  void setPlaylistPosition(uint8_t index, bool silent = false) {
    if (0 <= index && index < NBR_PLAYLISTS) {
      position[0] = index;
      updateCurrentItem();
      // Trigger the onSetPosition event
      if (!silent && onSetPosition != nullptr) {
        onSetPosition(position);
      }
    } else if (onError != nullptr) {
      onError(NULL, F("Wrong playlist index"));
      Serial.println(index);
      Serial.println(NBR_PLAYLISTS);
    }
  }

  // Définit la position dans la playlist
  void setPlayPosition(uint8_t index, bool silent = false) {
    if (0 <= index && index < NBR_PLAYLIST_ITEMS) {
      position[1] = index;
      updateCurrentItem();
      // Trigger the onSetPlayPosition event
      if (!silent && onSetPosition != nullptr) {
        onSetPosition(position);
      }
    } else if (onError != nullptr) {
      onError(NULL, F("Wrong item index"));
    }
  }

  PlaylistItem *getItem() {
    return current;
  }

  PlaylistItem *getItem(uint8_t index) {
    if (0 <= index < NBR_PLAYLIST_ITEMS) {
      return &playlists[position[0]][index];
    } else if (onError != nullptr) {
      onError(NULL, F("Wrong item index"));
    }
    return &emptyItem;
  }

  // Définit les deux curseurs de position
  void setPosition(uint8_t index[2], bool silent = false) {
    if (0 <= index[0] < NBR_PLAYLISTS && 0 <= index[1] < NBR_PLAYLIST_ITEMS) {
      position[0] = index[0];
      position[1] = index[1];
      // Trigger the onSetPosition event
      if (!silent && onSetPosition != nullptr) {
        onSetPosition(position);
      }
    } else if (onError != nullptr) {
      onError(NULL, F("Wrong playlist or item index"));
    }
  }

  // Sauve le fichier du filePicker dans la position
  void addCurrentFile(FilePicker *filePicker) {
    if (filePicker->exist()) {
      current->dirNum = filePicker->dirNum;
      current->fileNum = filePicker->fileNum;
      strncpy(current->dirName, filePicker->dirname + 3, nameSize);
      strncpy(current->fileName, filePicker->filename, nameSize);
    }
  }
  // Sauve le fichier du filePicker dans la position
  void loadM3U(FilePicker *filePicker) {
    
    for (uint8_t i = 0; i < NBR_PLAYLISTS; ++i) {

      File file = filePicker->getByNum(filePicker->SD->open("/"), i, FILE_ONLY, ".m3u");

      if (!file) {
        continue;
      }

      if (onConfirm != nullptr) {
        char name[100];
        file.getName(name, sizeof(name));
        onConfirm(name, F(" founded"));
      }

      char line[560]; // Maximum line length plus space for zero byte.
      size_t n;
      uint8_t playPosition = 0;

      setPlaylistPosition(i);

      while ((n = file.fgets(line, sizeof(line))) > 0) {

        if (line[0] != '#') {

          if (playPosition < NBR_PLAYLIST_ITEMS) {

            int8_t dirNum = -1;
            int8_t fileNum = -1;

            if (filePicker->getNumsFromPath(line, dirNum, fileNum)) {

              filePicker->select(dirNum, fileNum);

              if (filePicker->exist()) {

                setPlayPosition(playPosition);
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
    }
    // On réinitialise les positions
    setPlaylistPosition(0);
    setPlayPosition(0);
    onConfirm(NULL, F("M3U Chargement OK!"));
  }
};

#endif
