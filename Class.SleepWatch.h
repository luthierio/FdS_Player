#include <Arduino.h>

class SleepWatch {
private:
  bool SLEEPING;
  const unsigned long THRESHOLD = 5000;
public:
  unsigned long lastActivityTime;
  SleepWatch(const unsigned long threshold): THRESHOLD(threshold) {
    SLEEPING = false;
    lastActivityTime = millis();
  }

  void wakeUp() {
    // Réveiller le système ici (par exemple, désactiver le mode veille)
    SLEEPING = false;
    lastActivityTime = millis(); // Réinitialiser le temps d'activité
  }

  void listen() {
    unsigned long currentTime = millis();

    // Vérifier si le temps d'inactivité dépasse le seuil
    if (currentTime - lastActivityTime >= THRESHOLD) {
      SLEEPING = true;
    }
  }

  void activityDetected() {
    // Appelez cette fonction lorsque l'activité est détectée
    wakeUp(); // Réinitialiser le temps d'activité
  }

  bool isSleeping() {
    return SLEEPING;
  }
};
