
#ifndef Display_H   // Vérifie si MACLASSE_H n'a pas été défini
#define Display_H   // Définit MACLASSE_H pour éviter les inclusions multiples

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
      ecran_.setTextWrap(false);
      ecran_.setTextColor(SSD1306_WHITE);
      ecran_.cp437(true);
    }

    // Effacer l'affichage
    void clear() {
      ecran_.clearDisplay();
    }

    /**********************
    * LOGO
    ***********************/
    void logo() {
      ecran_.drawBitmap (0,0, LOGO_128x64, 128,64, 1); 
      ecran_.display();
    }

    /**********************
    * PLAYER
    ***********************/
    void printPath(FilePicker *selectedPath) {
      
      //On efface la zone   
      ecran_.fillRect(0, 0, 100, 12, BLACK); 
      printDirPath(selectedPath, 0, 3);

      ecran_.fillRect(0, 18, 128, 44, BLACK); 
      printFilePath(selectedPath, 0, 36, &FreeSerif9pt7b);

    }

    void printDirPath(FilePicker *selectedPath, int x, int y, const GFXfont *font = NULL, uint8_t textSize = 1){
      

      char dirNum[2];
      sprintf(dirNum, "%02d", selectedPath->dirNum );  

      if(!selectedPath->dirname[0] == '\0'){
        ecran_.drawBitmap (x, y, folderIcon8, 8,8,WHITE);
        printTxt(selectedPath->dirname+3, x+12, y);
      }else{
        printTxt(dirNum, x, y, font, textSize)  ;
        printTxt("Aucun dossier", x+20, y);
      }  
    }
    
    void printFilePath(FilePicker *selectedPath, int x, int y, const GFXfont *font = NULL, uint8_t textSize = 1) {
      char fileNum[3];
      sprintf(fileNum, "%02d", selectedPath->fileNum);

      if (!selectedPath->filename || selectedPath->filename[0] == '\0') {
        printTxt(fileNum, x, y, font, textSize);
        //Petits points
        ecran_.setCursor(x + 20, y);
        for (int px = x + 22; px < 128; px += 3) {
          ecran_.drawPixel(px, y + 2, WHITE);
        }
      } else {
        char displayedFile[255]; // Assurez-vous que la taille est suffisamment grande
        char fileInfos[255]; // Assurez-vous que la taille est suffisamment grande
        fileInfos[0] = '\0';
        strcpy(displayedFile, selectedPath->filename + 3); // Copie à partir du 4ème caractère
        displayedFile[strcspn(displayedFile, ".")] = '\0'; // Ajoute un caractère de fin de chaîne à la position du point
        const char *startBracket = strchr(displayedFile, '[');
        if (startBracket != NULL) {
          displayedFile[strcspn(displayedFile, "[")] = '\0'; // Ajoute un caractère de fin de chaîne à la position du point
          getBracketContent(selectedPath->filename, fileInfos, sizeof(fileInfos));
        }


        printTxt(displayedFile, x, y, font, textSize);
        printTxt(fileInfos, x, y + 10, NULL, textSize);
      }
    }
    // Fonction pour obtenir le contenu entre crochets
    void getBracketContent(const char *input, char *output, size_t outputSize) {
      const char *startBracket = strchr(input, '[');
      if (startBracket != NULL) {
        const char *endBracket = strchr(startBracket + 1, ']');
        if (endBracket != NULL) {
          size_t contentLength = endBracket - (startBracket + 1);
          strncpy(output, startBracket + 1, min(contentLength, outputSize - 1));
          output[min(contentLength, outputSize - 1)] = '\0'; // Ajoute un caractère de fin de chaîne
        }
      }
    }

    /**********************
    * GLOBAL
    ***********************/
    void analogGauges(float VUsb, float VBat, int Volume, int8_t x, int8_t y, uint8_t w, uint8_t h){  
    
      ecran_.fillRect(x,y, w, h,  BLACK);
      ecran_.drawRoundRect(x,y, w, h ,1, WHITE);
      if ( VUsb > 4.75) {
        ecran_.drawBitmap (x+5, y+3, alimIconH, 16, 7 ,WHITE);
      }else{
        uint8_t batLevel = map((int)(VBat*10), (int)(MIN_VBAT*10) , (int)(MAX_VBAT*10), 0, w); 
        HGauge(x+3, y+3, w-6,batLevel);    
      }   
      uint8_t volumeLevel = map(Volume, 0,MIN_VOLUME, w-6, 0);      // On echelonne le volume sur 20px
      HGauge(x+3, y+h/2+2,w-6,volumeLevel);
    }
    void VGauge(uint8_t x, uint8_t y,uint8_t h,uint8_t value){  
      //Height = 3
      ecran_.drawFastHLine(x, y,3, WHITE);
      ecran_.drawFastHLine(x, y+h-1,3, WHITE);
      ecran_.drawFastVLine(x+1, y,h, WHITE);
      ecran_.fillRect(x+1, y-1+h-value, 3, value-2, WHITE);
    }

    void HGauge(uint8_t x, uint8_t y,uint8_t w,uint8_t value){  
      //Height = 3
      ecran_.drawFastVLine(x, y,3, WHITE);
      ecran_.drawFastVLine(x+w-1, y,3, WHITE);
      ecran_.drawFastHLine(x, y+1,w, WHITE);
      ecran_.fillRect(x, y, value, 3 , WHITE);
    }

    // Afficher un texte
    void printNum(const int num, uint8_t x = 0, uint8_t y = 0, const GFXfont *font = NULL, uint8_t tailleTexte = 1, bool color = WHITE) {
      ecran_.setFont(font);
      ecran_.setTextColor(color);
      ecran_.setTextSize(tailleTexte);
      ecran_.setCursor(x, y);
      ecran_.print(num);
    }
    void printTxt(const char *texte, uint8_t x = 0, uint8_t y = 0, const GFXfont *font = NULL, uint8_t tailleTexte = 1, bool color = WHITE) {

      int16_t  x1, y1;
      uint16_t w, h;

      
      ecran_.setFont(font);
      ecran_.setTextColor(color);
      ecran_.setTextSize(tailleTexte);
      ecran_.setCursor(x, y);
      /*
      ecran_.getTextBounds(texte, x, y, &x1, &y1, &w, &h);
      if(font){
        ecran_.fillRect(x, y, w, h*2, BLACK); 
      }else{
        ecran_.setCursor(x, y);
        ecran_.fillRect(x, y, w, h, BLACK); 
      }
      */

      ecran_.print(texte);
    }

    // Rafraîchir l'affichage
    void show() {
      ecran_.display();
    }


  private:
    Adafruit_SSD1306 &ecran_;  // Référence vers l'objet Adafruit_SSD1306
  };

#endif
