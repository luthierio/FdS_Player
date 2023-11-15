#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display {
public:
  // Constructeur prenant un objet Adafruit_SSD1306 en paramètre
  Display(Adafruit_SSD1306 &ecran) : ecran_(ecran) {}

  // Initialisation de l'affichage
  void initialiser() {
    ecran_.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    ecran_.clearDisplay();
    ecran_.setTextSize(1);
    ecran_.setTextColor(SSD1306_WHITE);
  }

  // Effacer l'affichage
  void effacer() {
    ecran_.clearDisplay();
  }

  // Afficher un texte
  void logo() {
    ecran_.clearDisplay();
    ecran_.drawBitmap (0,0, LOGO_128x64, 128,64, 1); 
    ecran_.display();
  }
  // Afficher un texte
  void afficherTexte(const char *texte, uint8_t tailleTexte = 1, uint8_t ligne = 0, uint8_t colonne = 0) {
    ecran_.setTextSize(tailleTexte);
    ecran_.setCursor(colonne * (6 * tailleTexte), ligne * (8 * tailleTexte));
    ecran_.print(texte);
  }

  // Afficher un rectangle plein
  void afficherRectanglePlein(int16_t x, int16_t y, int16_t largeur, int16_t hauteur, uint16_t couleur) {
    ecran_.fillRect(x, y, largeur, hauteur, couleur);
  }

  // Rafraîchir l'affichage
  void rafraichir() {
    ecran_.display();
  }

private:
  Adafruit_SSD1306 &ecran_;  // Référence vers l'objet Adafruit_SSD1306
};

