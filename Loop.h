
/**********************
* LOOP
***********************/

void loop() {
  // File is playing in the background
  if (Serial.available()) {
    char c = Serial.read();

    // if we get an 's' on the serial console, play it!
    if (c == 'a') {
      if(ASF_DEBUG_MODE) Serial.println(F("⋅⋅⋅ ⋅ Playing UTF-8 File"));
      musicPlayer.startPlayingFile("/00 Renée Lebas/14 L'accordéoniste.mp3");
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


