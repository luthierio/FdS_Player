t_fileData &getFileDataRef(int dirNum, int fileNum) {
    // Si il existe et n'est pas vide, on l'utilise
    for (byte i = 0; i < MAX_FILES_DATA; i = i + 1) {
        if (dirNum == DATAS[i].dirNum && DATAS[i].fileNum == fileNum) {
            return DATAS[i];
        }
    }

    // Sinon on prend le prochain espace vide comme référence
    for (byte i = 0; i < MAX_FILES_DATA; i = i + 1) {
        if (DATAS[i].markers.isEmpty()) {            
            return DATAS[i];
        }
    }

    // Si on a rien trouvé de disponible, on envoie un tableau qui se vide et ne se sauve pas
    // Il faudra avertir l'utilisateur sur l'écran
    DEBUG_.print(F("Plus de place disponible pour de nouveau marqueurs. Impossible de sauver."));  
    emptyData.clear();
    return emptyData;
}
