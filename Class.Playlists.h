#include <Arduino.h>

#ifndef NBR_PLAYLISTS
#define NBR_PLAYLISTS 8 // Nombre de playlists
#endif

#ifndef NBR_PLAYLIST_ITEMS
#define NBR_PLAYLIST_ITEMS 20 // Nombre de références par playlist
#endif


struct PlaylistItem {
    int8_t dirNum = -1;
    int8_t fileNum = -1;
    static const uint8_t nameSize = 18;
    char dirName[nameSize] = {};
    char fileName[nameSize] = {};

    PlaylistItem() = default;

    void clear() {
        dirNum = -1;
        fileNum = -1;
        memset(dirName, 0, nameSize);
        memset(fileName, 0, nameSize);
    }

    bool isEmpty() const {
        return (dirNum == -1);
    }

    void save(FilePicker *File_) {
        if (File_->exist()) {
            dirNum = File_->dirNum;
            fileNum = File_->fileNum;
            strncpy(dirName, File_->dirname + 3, nameSize);
            strncpy(fileName, File_->filename, nameSize);
        }
    }
};

class PlaylistManager {
private:
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

    uint8_t *getPosition() {
        return position;
    }

    void setPosition(uint8_t index, bool silent = false) {
        if (0 <= index && index < NBR_PLAYLISTS) {
            position[0] = index;
            // Trigger the onSetPosition event
            if (!silent && onSetPosition != nullptr) {
                onSetPosition(position);
            }
        }
    }

    void setPlayPosition(uint8_t index, bool silent = false) {
        if (0 <= index && index < NBR_PLAYLIST_ITEMS) {
            position[1] = index;
            // Trigger the onSetPlayPosition event
            if (!silent && onSetPosition != nullptr) {
                onSetPosition(position);
            }
        }
    }

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

    bool selectFile(FilePicker *filePicker) {
        PlaylistItem *current = &playlists[position[0]][position[1]];
        if (!current->isEmpty()) {
            filePicker->select(current->dirNum, current->fileNum);
            // Ajoutez le reste de votre logique pour sélectionner le fichier
            return true;
        }
        return false;
    }

    void addCurrentFile(FilePicker *filePicker) {
        playlists[position[0]][position[1]].save(filePicker);
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
