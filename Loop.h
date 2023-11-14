
/**********************
* LOOP
***********************/

void smallLoop() {
  if(!SLEEP_WATCH.isSleeping()){
  }
}

void bigLoop() {

  if(SLEEP_WATCH.isSleeping()){
  }

}

uint32_t smallLoopTime;
uint32_t bigLoopTime;
void loop() {


  if(AUDIO.playingMusic && SLEEP_WATCH.isSleeping()){
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


