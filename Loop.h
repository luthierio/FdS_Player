
/**********************
* LOOP
***********************/

void loop() {
  // File is playing in the background
  if (Serial.available()) {
    char c = Serial.read();

    if (c == '8' ) {
      PITCHER.setValue(16384);
    }
    if (c == '9' ) {
      PITCHER.setValue(-18432);
    }
    if (c == '0' || c == '1' ) {
      AUDIO.pausePlaying(true);
    }
    if (c == '0') {      
      if(getFilePathByNum(SD, activeSoundPath, 0, 14)){
        Serial.println(activeSoundPath);
      }
    }
    if (c == '1') {
      if(getFilePathByNum(SD, activeSoundPath, 1, 2)){
        Serial.println(activeSoundPath);
      }
    }
    if (c == '0' ||c == '1' ) {
      AUDIO.pausePlaying(false);
    }

    // if we get an 's' on the serial console, play it!
    if (c == 'a') {
      Serial.println(F(""));
      Serial.println(F(" ⋅⋅⋅ Playing ⋅⋅⋅ "));
      AUDIO.startPlayingFile(activeSoundPath);
      Serial.println(activeSoundPath);
    }
    if (c == 'i') {
      Path aSoundPath(activeSoundPath);
      Serial.println(F(""));
      Serial.println(F(" ⋅⋅⋅ Infos ⋅⋅⋅ "));
      Serial.println(aSoundPath.filename()+3);
      Serial.println(aSoundPath.suffix());
      Serial.println(aSoundPath.dirNum());
      Serial.println(aSoundPath.fileNum());
      char dirname[255];
      aSoundPath.getDirname(dirname,255);
      Serial.println(dirname+3);
    }

    // if we get an 's' on the serial console, stop!
    if (c == 's') {
      AUDIO.stopPlaying();
    }

    // if we get an 'p' on the serial console, pause/unpause!
    if (c == 'p') {
      if (! AUDIO.paused()) {
        if(ASF_DEBUG_MODE) Serial.println("Paused");
        AUDIO.pausePlaying(true);
      } else {
        if(ASF_DEBUG_MODE) Serial.println("Resumed");
        AUDIO.pausePlaying(false);
      }
    }
    if (c == 'l') {
      AUDIO.stopPlaying();
      // list files
      if(ASF_DEBUG_MODE) FS.print(SD.open("/"), 1, &Serial);
    }
  }
  if (!AUDIO.stopped()) {
    delay(100);
    if (! AUDIO.paused()) {
      if(ASF_DEBUG_MODE) Serial.print(".");
    }
  }
}


