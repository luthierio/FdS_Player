#ifndef ButtonHandler_H   // Vérifie si MACLASSE_H n'a pas été défini
#define ButtonHandler_H   // Définit MACLASSE_H pour éviter les inclusions multiples


  class ButtonHandler {
  public:
    ButtonHandler(int buttonCount, int debounceDelay = 200, int longPressDelay = 1000, int longReleaseDelay = 1000) 
      : buttonCount(buttonCount), debounceDelay(debounceDelay), longPressDelay(longPressDelay), longReleaseDelay(longReleaseDelay) {
      buttonStates = new bool[buttonCount];
      lastDebounceTimes = new unsigned long[buttonCount];
      buttonHoldStartTime = new unsigned long[buttonCount];
      listenLongPress = new bool[buttonCount];
      listenLongRelease = new bool[buttonCount];

      for (int i = 0; i < buttonCount; ++i) {
        buttonStates[i] = HIGH;
        lastDebounceTimes[i] = 0;
        listenLongPress[i] = false;
        listenLongRelease[i] = false;
      }
    }

    ~ButtonHandler() {
      delete[] buttonStates;
      delete[] lastDebounceTimes;
      delete[] buttonHoldStartTime;
      delete[] listenLongPress;
      delete[] listenLongRelease;
    }

    void setCallbacks(
      void (*onPressCallBack)(ButtonHandler*, int),
      void (*onReleaseCallBack)(ButtonHandler*, int),
      void (*onLongPressCallBack)(ButtonHandler*, int),
      void (*onLongReleaseCallBack)(ButtonHandler*, int)
      ) {
      onPress = onPressCallBack;
      onRelease = onReleaseCallBack;
      onLongPress = onLongPressCallBack;
      onLongRelease = onLongReleaseCallBack;
    }

    void update(int* externalButtonStates) {
      for (int i = 0; i < buttonCount; ++i) {
        int reading = externalButtonStates[i];

        if ((millis() - lastDebounceTimes[i]) > debounceDelay) {
          if (reading != buttonStates[i]) {
            lastDebounceTimes[i] = millis();
            buttonStates[i] = reading;
            buttonHoldStartTime[i] = millis();

            if (reading == LOW) {
              // Bouton enfoncé
              onPress(this, i);
              listenLongPress[i] = true;
            } else {
              // Bouton relâché
              onRelease(this, i);
              listenLongRelease[i] = true;
            }
          } else {
            if (reading == LOW && listenLongPress[i] && (millis() - buttonHoldStartTime[i] >= longPressDelay)) {
              // Appui long maintenu
              onLongPress(this, i);
              listenLongPress[i] = false;
            } else if (reading == HIGH && listenLongRelease[i] && (millis() - buttonHoldStartTime[i] >= longReleaseDelay)) {
              // Bouton relâché après un appui long
              onLongRelease(this, i);
              listenLongRelease[i] = false;
            }
          }
        }
      }
    }


  private:
    int buttonCount;
    int debounceDelay;
    int longPressDelay;
    int longReleaseDelay;
    bool *buttonStates;
    unsigned long *lastDebounceTimes;
    unsigned long *buttonHoldStartTime;
    bool *listenLongPress;
    bool *listenLongRelease;

    void (*onPress)(ButtonHandler*, int);  // Fonction de rappel pour traiter les boutons
    void (*onRelease)(ButtonHandler*, int);  // Fonction de rappel pour traiter les boutons
    void (*onLongPress)(ButtonHandler*, int);  // Fonction de rappel pour traiter les boutons
    void (*onLongRelease)(ButtonHandler*, int);  // Fonction de rappel pour traiter les boutons
  };

#endif
