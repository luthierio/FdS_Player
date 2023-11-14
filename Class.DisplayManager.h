#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class DisplayManager {
public:
  enum DisplayMode {
    MODE_NAVIGATION,
    MODE_PLAYLIST,
    MODE_SPLASH,
    MODE_METRONOME,
    MODE_MENU
  };

  DisplayManager(Adafruit_SSD1306& display) : display(display), currentMode(MODE_SPLASH) {}

  void begin() {
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    display.display();
    delay(2000);
    display.clearDisplay();
  }

  void switchOn() {
      display.ssd1306_command(SSD1306_DISPLAYON);
  }
  void switchOff() {
      display.ssd1306_command(SSD1306_DISPLAYOFF);
  }

  void switchMode(DisplayMode newMode) {
    currentMode = newMode;
    updateDisplay();
  }

  void updateDisplay() {
    switch (currentMode) {
      case MODE_NAVIGATION:
        displayNavigation();
        break;
      case MODE_PLAYLIST:
        displayPlaylist();
        break;
      case MODE_SPLASH:
        displaySplash();
        break;
      case MODE_METRONOME:
        displayMetronome();
        break;
      case MODE_MENU:
        displayMenu();
        break;
    }
  }

private:
  Adafruit_SSD1306& display;
  DisplayMode currentMode;

  void displayNavigation() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.print("Ecran de navigation");
    display.display();
  }

  void displayPlaylist() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.print("Ecran de playlist");
    display.display();
  }

  void displaySplash() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.print("Ecran de splash");
    display.display();
    delay(2000);
  }

  void displayMetronome() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.print("Ecran de metronome");
    display.display();
  }

  void displayMenu() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.print("Ecran de menu");
    display.display();
  }
};
