
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
      PITCHER.setValue(18432);
    }

    if (c == '0' || c == '1' || c == '2' ) {
      AUDIO.pausePlaying(true);
    }
    if (c == '0') {    
        STATE.dirNum = 0;
        STATE.fileNum = 0;
    }
    if (c == '1') {
        STATE.dirNum = 1;
        STATE.fileNum = 2;
    }
    if (c == '2') {
        STATE.dirNum = 0;
        STATE.fileNum = 14;
    }
    if (c == '0' ||c == '1'  ||c == '2' ) {
        FILE_.update();
      Serial.println(FILE_.path);
      AUDIO.pausePlaying(false);
    }

    // if we get an 's' on the serial console, play it!
    if (c == 'a') {
      Serial.println("");
      Serial.print(F(" ⋅⋅⋅ Playing ⋅⋅⋅ : "));
      Serial.println(FILE_.path);
      AUDIO.startPlayingFile(FILE_.path);
    }
    if (c == 'i') {
      Serial.println(FILE_.dirname+3);
      Serial.println(FILE_.filename+3);

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
      FILE_.print(SD.open("/"), 0,&Serial);
    }
  }
  if (!AUDIO.stopped()) {
    delay(100);
    if (! AUDIO.paused()) {
      if(ASF_DEBUG_MODE) Serial.print(".");
    }
  }
}


