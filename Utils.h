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

void readVolume() { 
 
  uint8_t reqVolume; //On enregistre temporairement le volume
  reqVolume = map(analogRead(VOLUME_PIN), 5, 1023, MAX_VOLUME, MIN_VOLUME);  

  if(reqVolume != VOLUME && reqVolume >= MIN_VOLUME-1){

    VOLUME = MIN_VOLUME;
    SLEEP_WATCH.keepAlive();
    AUDIO.setVolume(254,254); // VOL MIN doit etre sur off = 255   

  }else if(reqVolume != VOLUME && abs(reqVolume - VOLUME) > 2){  

    VOLUME = reqVolume;
    SLEEP_WATCH.keepAlive();
    AUDIO.setVolume(VOLUME,VOLUME); 

  }

}