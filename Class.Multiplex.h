class MultiplexedButtons {
public:
  // Valeur pour considérer un bouton HIGH malgré une lecture analogique
  const int threshold = 512; 
  // Constructeur
  MultiplexedButtons(const byte pinAddrA, const byte pinAddrB, const byte pinAddrC, const byte pinSig) 
    : PIN_ADDR_A(pinAddrA), PIN_ADDR_B(pinAddrB), PIN_ADDR_C(pinAddrC), PIN_SIG(pinSig) {
    // Initialisation des broches
  }
  
  void begin(){
    pinMode(PIN_ADDR_A, OUTPUT);
    pinMode(PIN_ADDR_B, OUTPUT);
    pinMode(PIN_ADDR_C, OUTPUT);
    pinMode(PIN_SIG, INPUT);
  }
  // Méthode pour lire les valeurs analogiques sur toutes les broches
  void readAnalogValues(int analogValues[8]) {
    for (byte i = 0; i < 8; ++i) {
      setAddress(i);
      analogValues[i] = analogRead(PIN_SIG);
    }
  }
  // Méthode pour lire l'état du bouton à une adresse donnée
  bool state(byte buttonAddress) {
    // Sélectionner l'adresse
    setAddress(buttonAddress);
    // Lire l'état du bouton
    return (analogRead(PIN_SIG) > threshold );
  }
  // Méthode pour lire l'état du bouton à une adresse donnée
  int value(byte buttonAddress) {
    // Sélectionner l'adresse
    setAddress(buttonAddress);

    // Lire l'état du bouton
    return analogRead(PIN_SIG);
  }

private:
  const byte PIN_ADDR_A;
  const byte PIN_ADDR_B;
  const byte PIN_ADDR_C;
  const byte PIN_SIG;

  // Méthode pour configurer les broches d'adresse
  void setAddress(byte address) {
    digitalWrite(PIN_ADDR_A, bitRead(address, 0));
    digitalWrite(PIN_ADDR_B, bitRead(address, 1));
    digitalWrite(PIN_ADDR_C, bitRead(address, 2));
  }
};
