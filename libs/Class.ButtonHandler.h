#ifndef ButtonHandler_H   // Vérifie si MACLASSE_H n'a pas été défini
#define ButtonHandler_H   // Définit MACLASSE_H pour éviter les inclusions multiples


  class ButtonHandler {
  public:
    ButtonHandler(int buttonCount, int debounceDelay = 50, int longPressDelay = 1000) 
      : buttonCount(buttonCount), debounceDelay(debounceDelay), longPressDelay(longPressDelay) {
      buttonStates = new bool[buttonCount];
      lastButtonStates = new bool[buttonCount];
      lastDebounceTimes = new unsigned long[buttonCount];
      buttonHoldStartTime = new unsigned long[buttonCount];
      acceptLongPress = new bool[buttonCount];

      for (int i = 0; i < buttonCount; ++i) {
        buttonStates[i] = false;
        lastButtonStates[i] = false;
        lastDebounceTimes[i] = 0;
        acceptLongPress[i] = false;
      }
    }

    ~ButtonHandler() {
      delete[] buttonStates;
      delete[] lastButtonStates;
      delete[] lastDebounceTimes;
      delete[] buttonHoldStartTime;
      delete[] acceptLongPress;
    }

    void setCallback(void (*callback)(ButtonHandler*, int, bool, bool)) {
      doStuff = callback;
    }

    void update(int* externalButtonStates) {
      for (int i = 0; i < buttonCount; ++i) {
        int reading = externalButtonStates[i];

        if (reading != lastButtonStates[i]) {
          lastDebounceTimes[i] = millis();
          acceptLongPress[i] = false;
        }

        if ((millis() - lastDebounceTimes[i]) > debounceDelay) {
          if (reading != buttonStates[i]) {
            buttonStates[i] = reading;

            if (reading == LOW) {
              // Bouton enfoncé
              doStuff(this, i, false, false);
              buttonHoldStartTime[i] = millis();
              acceptLongPress[i] = true;
            } else {
              // Bouton relâché
              if (millis() - buttonHoldStartTime[i] < longPressDelay && acceptLongPress[i]) {
                // Appui court
                doStuff(this, i, false, true);
              } else if (millis() - buttonHoldStartTime[i] >= longPressDelay && acceptLongPress[i]) {
                // Appui long
                doStuff(this, i, true, false);
              }

              // Réinitialiser l'état du bouton
              doStuff(this, i, false, true);
            }
          } else if (reading == HIGH && acceptLongPress[i] && (millis() - buttonHoldStartTime[i] >= longPressDelay)) {
            // Bouton maintenu enfoncé pour un appui long
            doStuff(this, i, true, false);
            acceptLongPress[i] = false;
          }
        }

        lastButtonStates[i] = reading;
      }
    }

  private:
    int buttonCount;
    int debounceDelay;
    int longPressDelay;
    bool *buttonStates;
    bool *lastButtonStates;
    unsigned long *lastDebounceTimes;
    unsigned long *buttonHoldStartTime;
    bool *acceptLongPress;

    void (*doStuff)(ButtonHandler*, int, bool, bool);  // Fonction de rappel pour traiter les boutons
  };

#endif