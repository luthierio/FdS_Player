
/**********************
* LOOP
***********************/
void smallLoop() {
  uint8_t space4Pitch = 0; // = 22;avec affichage Pitch

  switch (ASF_MODE) {
    case PLAYER:

      DISPLAY_.analogs.gauges(VUSB, VBat,VOLUME, 100, -2, 30, 18);


        if(FILE_.exist() && PITCHER.getStep() != 0){
          space4Pitch = SPACE_FOR_PITCH;
          DISPLAY_.display.cleanZone(128-space4Pitch, 50, space4Pitch , 14 );        
          DISPLAY_.pitcher.print(128-space4Pitch + 2  , 52 , 10 , 10 );     
        }
        
        DISPLAY_.display.cleanZone(0, 52, 128-space4Pitch, 12 );  

        if(FILE_.exist()){

          DISPLAY_.playing.progressBar(3, 57, 125-space4Pitch, 57, &DATA->markers);
          DISPLAY_.playing.playMode(125-space4Pitch, 57, STATE.playMode); 

        }  

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
  VBat = (float)round(10*(MUX.value(BTN_CHANNEL[1])* 3.3 * 2 )/ 1024.0)/10.0; // VERIFIER NUMERO!!
  setVolume(map(analogRead(VOLUME_PIN), 5, 1023, MAX_VOLUME, MIN_VOLUME));

  if (millis() - smallLoopTime >= SMALL_LOOP_INTERVAL){
    smallLoopTime = millis();
    smallLoop();
  }    
  if (millis() - bigLoopTime >= BIG_LOOP_INTERVAL){
    bigLoopTime = millis();
    bigLoop();
  }
}


