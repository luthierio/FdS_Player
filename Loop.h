
/**********************
* LOOP
***********************/

void loop() {
  // File is playing in the background
  if (Serial.available()) {
    char c = Serial.read();

    if (c == '0') {
      getFilePathByNum(SD, activeSoundPath, 0, 14);
      Serial.println(activeSoundPath);
      aSoundPath = Path(activeSoundPath);
      /*
      if(ASF_DEBUG_MODE) Serial.println(aSoundPath.dirNum());
      if(ASF_DEBUG_MODE) Serial.println(aSoundPath.fileNum());
      */

    }
    if (c == '1') {
      getFilePathByNum(SD, activeSoundPath, 1, 2);
      Serial.println(activeSoundPath);
      aSoundPath = Path(activeSoundPath);
    }

    if (c == 'r') {
       aSoundPath = Path("/00 Renée Lebas/14 L'accordéoniste.mp3");
    }
    if (c == 't') {
      aSoundPath = Path("/01 Django/02 Saint Louis Blues [ I Got Rhythm (1941)].mp3");
    }
    if (c == 'y') {
      aSoundPath = Path("track001.mp3");
    }
    if (c == 'u') {
      aSoundPath = Path("/track002.mp3");
    }
    // if we get an 's' on the serial console, play it!
    if (c == 'a') {
      if(ASF_DEBUG_MODE) Serial.println(F(" ⋅ Playing UTF-8 File ⋅ "));

      char tmpPath[512];
      strcpy (tmpPath,aSoundPath.get());
      tmpPath[strlen(aSoundPath.get())] =  '\0';
      musicPlayer.startPlayingFile(tmpPath);
      if(ASF_DEBUG_MODE) Serial.println(tmpPath);
    }
    if (c == 'i') {
      if(ASF_DEBUG_MODE) Serial.println(F(""));
      if(ASF_DEBUG_MODE) Serial.println(F(" ⋅⋅⋅ Infos ⋅⋅⋅ "));
      if(ASF_DEBUG_MODE) Serial.println(aSoundPath.filename());
      if(ASF_DEBUG_MODE) Serial.println(aSoundPath.suffix());
      if(ASF_DEBUG_MODE) Serial.println(aSoundPath.dirNum());
      if(ASF_DEBUG_MODE) Serial.println(aSoundPath.fileNum());
      char dirname[255];
      aSoundPath.getDirname(dirname,255);
      if(ASF_DEBUG_MODE) Serial.println(dirname);
    }
    // if we get an 's' on the serial console, stop!
    if (c == 's') {
      musicPlayer.stopPlaying();
    }

    // if we get an 'p' on the serial console, pause/unpause!
    if (c == 'p') {
      if (! musicPlayer.paused()) {
        if(ASF_DEBUG_MODE) Serial.println("Paused");
        musicPlayer.pausePlaying(true);
      } else {
        if(ASF_DEBUG_MODE) Serial.println("Resumed");
        musicPlayer.pausePlaying(false);
      }
    }
    if (c == 'l') {
      musicPlayer.stopPlaying();
      // list files
      if(ASF_DEBUG_MODE) printDirectory(SD.open("/"), 1);
    }
  }
  if (!musicPlayer.stopped()) {
    delay(100);
    if (! musicPlayer.paused()) {
      if(ASF_DEBUG_MODE) Serial.print(".");
    }
  }
}


