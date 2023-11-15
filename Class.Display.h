#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display {
public:
  // Constructeur prenant un objet Adafruit_SSD1306 en paramètre
  Display(Adafruit_SSD1306 &ecran) : ecran_(ecran) {}

  // Initialisation de l'affichage
  void init() {
    ecran_.clearDisplay();
    ecran_.setTextSize(1);
    ecran_.setTextColor(SSD1306_WHITE);
    logo();
  }

  // Effacer l'affichage
  void clear() {
    ecran_.clearDisplay();
  }

  // Afficher un texte
  void logo() {
    ecran_.clearDisplay();
    ecran_.clearDisplay();
    ecran_.drawBitmap (0,0, LOGO_128x64, 128,64, 1); 
    ecran_.display();
  }

  // Afficher un texte
  void printPath(FilePicker *selectedPath) {
    ecran_.clearDisplay();
    txt(selectedPath->path);
    ecran_.display();
  }


  // Afficher un texte
  void txt(const char *texte, uint8_t tailleTexte = 1, uint8_t x = 0, uint8_t y = 0, bool color = WHITE) {
    ecran_.setFont();
    ecran_.setTextColor(color);
    ecran_.setTextSize(tailleTexte);
    ecran_.setCursor(x, y);
    ecran_.print(texte);
  }

  // Rafraîchir l'affichage
  void show() {
    ecran_.display();
  }


private:
  Adafruit_SSD1306 &ecran_;  // Référence vers l'objet Adafruit_SSD1306
};

