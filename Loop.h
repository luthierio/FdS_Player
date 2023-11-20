
/**********************
* LOOP
***********************/
void smallLoop() {


  uint8_t space4Pitch = 0; // = 22;avec affichage Pitch
  switch (ASF_MODE) {
    case PLAYER:
      DISPLAY_.analogs.gauges(VUSB, VBat,VOLUME, 100, -2, 30, 18);
      if(PITCHER.getStep() != 0){
        DISPLAY_.playing.progressBar(3, 57, 125-SPACE_FOR_PITCH, 57, true);
        DISPLAY_.display.cleanZone(128-SPACE_FOR_PITCH, 52, SPACE_FOR_PITCH , 12 );        
        DISPLAY_.pitcher.printSymbol(128-SPACE_FOR_PITCH + 2  , 52 , 10 , 10 );            
        DISPLAY_.pitcher.printValue (128-SPACE_FOR_PITCH + 12+4 , 52+2 );     
      }else{
        DISPLAY_.display.cleanZone(0, 52, 128 , 12 );   
        DISPLAY_.playing.progressBar(3, 57, 125, 57, true);
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

  if(SLEEP_WATCH.isSleeping()){ 

   }

  if(AUDIO.playingMusic){
    //Serial.println(AUDIO.getBitRate());
  }

}

uint32_t smallLoopTime;
uint32_t bigLoopTime;
void loop() {

  if(AUDIO.playingMusic){
    SLEEP_WATCH.keepAlive();
  }
  
  SLEEP_WATCH.listen();
  //Lancé à intervale réduit


  // Mettre à jour en continu le rotary encoder
  for (byte i = 0; i < 3; ++i) {
    ROTARIES[i].update();    
  }

  // Mettez à jour les états des boutons en lisant les broches ici
  int BTN_STATE[6];
  for (int i = 0; i < 6; i++) {
    BTN_STATE[i] = MUX.state(BTN_CHANNEL[i]);
  }

  VUSB = (float)round(10*(MUX.value(BTN_CHANNEL[0])* 3.3 * 2 )/ 1024.0)/10.0;
  VBat = (float)round(10*(MUX.value(BTN_CHANNEL[1])* 3.3 * 2 )/ 1024.0)/10.0; // VERIFIER NUMERO!!
  setVolume(map(analogRead(VOLUME_PIN), 5, 1023, MAX_VOLUME, MIN_VOLUME));

  // Passez les états des boutons à la classe ButtonHandler pour la gestion
  BUTTONS.update(BTN_STATE);

  if (millis() - smallLoopTime >= SMALL_LOOP_INTERVAL){
    smallLoopTime = millis();
    smallLoop();
  }    
  if (millis() - bigLoopTime >= BIG_LOOP_INTERVAL){
    bigLoopTime = millis();
    bigLoop();
  }  
  
}


