
/**********************
* LOOP
***********************/

void smallLoop() {
  if(!SLEEP_WATCH.isSleeping()){
    DISPLAY_.show();

  }
}

void bigLoop() {

  switch (ASF_MODE) {
    default:
      DISPLAY_.analogGauges(VUSB, VBat,30, 100, -2, 30, 18);
      break;
  }

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


