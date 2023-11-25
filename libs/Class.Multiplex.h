#ifndef Multiplex_H   // Vérifie si MACLASSE_H n'a pas été défini
#define Multiplex_H   // Définit MACLASSE_H pour éviter les inclusions multiples

  class Multiplex {
  public:
    // Valeur pour considérer un bouton HIGH malgré une lecture analogique
    const int threshold; 
    // Constructeur
    Multiplex(const byte pinAddrA, const byte pinAddrB, const byte pinAddrC, const byte pinSig, int threshold = 512) 
      : MUX_PIN_ADDR_A(pinAddrA), MUX_PIN_ADDR_B(pinAddrB), MUX_PIN_ADDR_C(pinAddrC), MUX_PIN_SIG(pinSig), threshold(threshold) {
      // Initialisation des broches
    }
    
    void begin(){
      pinMode(MUX_PIN_ADDR_A, OUTPUT);
      pinMode(MUX_PIN_ADDR_B, OUTPUT);
      pinMode(MUX_PIN_ADDR_C, OUTPUT);
      //digitalWrite(PIN_ADDR_A, LOW);
      //digitalWrite(PIN_ADDR_B, LOW);
      //digitalWrite(PIN_ADDR_C, LOW);
      pinMode(MUX_PIN_SIG, INPUT);
    }
    // Méthode pour lire les valeurs analogiques sur toutes les broches
    void readAnalogValues(int analogValues[8]) {
      for (byte i = 0; i < 8; ++i) {
        setAddress(i);
        analogValues[i] = analogRead(MUX_PIN_SIG);
      }
    }
    // Méthode pour lire l'état du bouton à une adresse donnée
    bool state(byte buttonAddress) {
      // Sélectionner l'adresse
      setAddress(buttonAddress);
      // Lire l'état du bouton
      return (analogRead(MUX_PIN_SIG) > threshold );
    }
    // Méthode pour lire l'état du bouton à une adresse donnée
    int value(byte buttonAddress) {
      // Sélectionner l'adresse
      setAddress(buttonAddress);

      // Lire l'état du bouton
      return analogRead(MUX_PIN_SIG);
    }

  private:
    const byte MUX_PIN_ADDR_A;
    const byte MUX_PIN_ADDR_B;
    const byte MUX_PIN_ADDR_C;
    const byte MUX_PIN_SIG;

    // Méthode pour configurer les broches d'adresse
    void setAddress(byte address) {
      digitalWrite(MUX_PIN_ADDR_A, bitRead(address, 0));
      digitalWrite(MUX_PIN_ADDR_B, bitRead(address, 1));
      digitalWrite(MUX_PIN_ADDR_C, bitRead(address, 2));
    }
  };

#endif
