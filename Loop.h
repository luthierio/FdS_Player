
/**********************
* LOOP
***********************/
void smallLoop() {


  switch (STATE.MODE) {
    case PLAYER:
      //To be moved to display player show()
      DISPLAY_.analogs.gauges(VUSB, VBat,VOLUME, 100, -2, 30, 18);
      DISPLAY_.display.cleanZone(0, 52, 128, 64);  
      DISPLAY_.playing.fullProgressBar(0, 58, 128, 58, 10, 25);
      break;

    case PLAYLIST:
      DISPLAY_.display.cleanZone(118, 0, 118, 64 );  
      DISPLAY_.playing.progressBar(124, 0, 124, 64, 10);
      DISPLAY_.playlists.loop(); 
      break;

    default:
      break;
  }

  if(!SLEEP_WATCH.isSleeping()){
    DISPLAY_.show();
  }
}
void bigLoop() {


}

uint32_t smallLoopTime;
uint32_t bigLoopTime;
void loop() {
  
  if(AUDIO.playingMusic){
    SLEEP_WATCH.keepAlive();
  }
  
  SLEEP_WATCH.listen();
  autoPlay();

  if(INTERRUPTS){
    // Mettre à jour en continu le rotary encoder
    for (byte i = 0; i < 3; ++i) {
      ROTARIES[i].update();    
    }

    // Mettez à jour les états des boutons en lisant les broches ici
    int BTN_STATE[6];
    for (int i = 0; i < 6; i++) {
      BTN_STATE[i] = MUX.state(BTN_CHANNEL[i]);
    }
    // Passez les états des boutons à la classe ButtonHandler pour la gestion
    BUTTONS.update(BTN_STATE);
    VUSB = (float)round(10*(MUX.value(BTN_CHANNEL[0])* 3.3 * 2 )/ 1024.0)/10.0;
    VBat = (float)round(10*(MUX.value(BTN_CHANNEL[1])* 3.3 * 2 )/ 1024.0)/10.0;
    setVolume(map(analogRead(VOLUME_PIN), 5, 1023, MAX_VOLUME, MIN_VOLUME));
  }


  if (millis() - smallLoopTime >= SMALL_LOOP_INTERVAL){
    smallLoopTime = millis();
    smallLoop();
  }    
  if (millis() - bigLoopTime >= BIG_LOOP_INTERVAL){
    bigLoopTime = millis();
    bigLoop();
  }
}


