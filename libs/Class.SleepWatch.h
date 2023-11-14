#ifndef SleepWatch_H
#define SleepWatch_H

  class SleepWatch {

  private:
      bool SLEEPING;
      const unsigned long THRESHOLD = 5000;

  public:
      unsigned long lastActivityTime;

      // Fonctions de rappel externes
      void (*onSleep)();
      void (*onWakeUp)();

      SleepWatch(const unsigned long threshold) : THRESHOLD(threshold), onSleep(nullptr), onWakeUp(nullptr) {
          SLEEPING = false;
          lastActivityTime = millis();
      }

      // Fonction pour définir les callbacks après l'initialisation
      void setCallbacks(void (*sleepCallback)(), void (*wakeUpCallback)()) {
          onSleep = sleepCallback;
          onWakeUp = wakeUpCallback;
      }

      void wakeUp() {
          SLEEPING = false;
          lastActivityTime = millis();
          if (onWakeUp != nullptr) {
              onWakeUp();
          }
      }

      void listen() {
          unsigned long currentTime = millis();

          if (currentTime - lastActivityTime >= THRESHOLD) {
              SLEEPING = true;
              if (onSleep != nullptr) {
                  onSleep();
              }
          }
      }

      void activityDetected() {
          wakeUp();
      }

      bool isSleeping() {
          return SLEEPING;
      }
};

#endif

