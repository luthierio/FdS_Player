t_fileData &getFileDataRef(int dirNum, int fileNum) {
    // Si il existe et n'est pas vide, on l'utilise
    for (byte i = 0; i < NBR_FILES_DATA; i = i + 1) {
        if (dirNum == DATAS[i].dirNum && DATAS[i].fileNum == fileNum) {
            return DATAS[i];
        }
    }

    // Sinon on prend le prochain espace vide comme référence
    for (byte i = 0; i < NBR_FILES_DATA; i = i + 1) {
        if (DATAS[i].markers.isEmpty()) {
            return DATAS[i];
        }
    }

    // Si on a rien trouvé de disponible, on écrase le premier
    return DATAS[0];
}
