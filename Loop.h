
/**********************
* LOOP
***********************/

void loop() {
  // Mettre à jour en continu le rotary encoder
  for (byte i = 0; i < 3; ++i) {
    ROTARIES[i].update();    
  }

  // Mettez à jour les états des boutons en lisant les broches ici
  for (int i = 0; i < 6; i++) {
    BTN_STATE[i] = !MUX.state(BTN_CHANNEL[i]);
  }
  // Passez les états des boutons à la classe ButtonHandler pour la gestion
  BUTTONS.update(BTN_STATE);
  
}


