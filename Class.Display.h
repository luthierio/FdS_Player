
#ifndef Display_H   // Vérifie si MACLASSE_H n'a pas été défini
#define Display_H   // Définit MACLASSE_H pour éviter les inclusions multiples

  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>

  /**********************
  * MAIN Class:
  ***********************/
  class Display {
  public:
      Display(Adafruit_SSD1306 *ecran) : ecran_(ecran) {}

      void init() {
          ecran_->clearDisplay();
          ecran_->setTextSize(1);
          ecran_->setTextWrap(false);
          ecran_->setTextColor(SSD1306_WHITE);
          ecran_->cp437(true);
      }

      void clear() {
          ecran_->clearDisplay();
      }

      void show() {
          ecran_->display();
      }
      void logo() {
        ecran_->drawBitmap (0,0, LOGO_128x64, 128,64, 1); 
        ecran_->display();
      }


      // Afficher un texte
      void printNum(const int num, uint8_t x = 0, uint8_t y = 0, const GFXfont *font = NULL, uint8_t tailleTexte = 1, bool color = WHITE) {
        ecran_->setFont(font);
        ecran_->setTextColor(color);
        ecran_->setTextSize(tailleTexte);
        ecran_->setCursor(x, y);
        ecran_->print(num);
      }

      void printTxt(const char *texte, uint8_t x = 0, uint8_t y = 0, const GFXfont *font = NULL, uint8_t tailleTexte = 1, bool color = WHITE) {

        int16_t  x1, y1;
        uint16_t w, h;

        
        ecran_->setFont(font);
        ecran_->setTextColor(color);
        ecran_->setTextSize(tailleTexte);
        ecran_->setCursor(x, y);
        /*
        ecran_->getTextBounds(texte, x, y, &x1, &y1, &w, &h);
        if(font){
          ecran_->fillRect(x, y, w, h*2, BLACK); 
        }else{
          ecran_->setCursor(x, y);
          ecran_->fillRect(x, y, w, h, BLACK); 
        }
        */

        ecran_->print(texte);
      }
      

  protected:
      Adafruit_SSD1306 *ecran_;
  };

  /**********************
  * FICHIERS:
  ***********************/
  class FileDisplay : public Display {
  public:
      FileDisplay(Adafruit_SSD1306 *ecran) : Display(ecran) {}

      void printPath(FilePicker *selectedPath) {
        
        //On efface la zone   
        ecran_->fillRect(0, 0, 100, 12, BLACK); 
        printDirPath(selectedPath, 0, 3);

        ecran_->fillRect(0, 18, 128, 44, BLACK); 
        printFilePath(selectedPath, 0, 32, &FreeSerif9pt7b);

      }

      void printDirPath(FilePicker *selectedPath, int x, int y, const GFXfont *font = NULL, uint8_t textSize = 1){
        

        char dirNum[2];
        sprintf(dirNum, "%02d", selectedPath->dirNum );  

        if(!selectedPath->dirname[0] == '\0'){
          ecran_->drawBitmap (x, y, folderIcon8, 8,8,WHITE);
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
          ecran_->setCursor(x + 20, y);
          for (int px = x + 22; px < 128; px += 3) {
            ecran_->drawPixel(px, y + 2, WHITE);
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
  };

  /**********************
  * ANALOGIQUES (Energie & volume):
  ***********************/
  class AnalogDisplay : public Display {
  public:
      AnalogDisplay(Adafruit_SSD1306 *ecran) : Display(ecran) {}

      void gauges(float VUsb, float VBat, int Volume, int8_t x, int8_t y, uint8_t w, uint8_t h){  
      
        ecran_->fillRect(x,y, w, h,  BLACK);
        ecran_->drawRoundRect(x,y, w, h ,1, WHITE);
        if ( VUsb > 4.5) {
          ecran_->drawBitmap (x+5, y+3, alimIconH, 16, 7 ,WHITE);
        }else{
          uint8_t batLevel = map((int)(VBat*10), (int)(MIN_VBAT*10) , (int)(MAX_VBAT*10), 0, w); 
          HGauge(x+3, y+3, w-6,batLevel);    
        }   
        uint8_t volumeLevel = map(Volume, 0,MIN_VOLUME, w-6, 0);      // On echelonne le volume sur 20px
        HGauge(x+3, y+h/2+2,w-6,volumeLevel);
      }
      void VGauge(uint8_t x, uint8_t y,uint8_t h,uint8_t value){  
        //Height = 3
        ecran_->drawFastHLine(x, y,3, WHITE);
        ecran_->drawFastHLine(x, y+h-1,3, WHITE);
        ecran_->drawFastVLine(x+1, y,h, WHITE);
        ecran_->fillRect(x+1, y-1+h-value, 3, value-2, WHITE);
      }

      void HGauge(uint8_t x, uint8_t y,uint8_t w,uint8_t value){  
        //Height = 3
        ecran_->drawFastVLine(x, y,3, WHITE);
        ecran_->drawFastVLine(x+w-1, y,3, WHITE);
        ecran_->drawFastHLine(x, y+1,w, WHITE);
        ecran_->fillRect(x, y, value, 3 , WHITE);
      }
  };

  /**********************
  * PROGRESSBAR:
  ***********************/

  class PlayingDisplay : public Display {
  public:
      PlayingDisplay(Adafruit_SSD1306 *ecran, FdS_Adafruit_VS1053_FilePlayer *player) : 
        Display(ecran),
        Player (player){}

      void progressBar(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, boolean markersOn){  

        ecran_->fillRect(x1-2,y1-2, x2-x1+4, 5,  BLACK);
        
        ecran_->drawLine(x1,y1,x2,y2, WHITE);
        ecran_->fillCircle(x1,y1, 2, WHITE);
        ecran_->fillCircle(x2,y2, 2, WHITE);
        
        int delta_X = x2-x1; //Delta X
        int delta_Y = y2-y1; //Delta Y
          
          
        float L = sqrt(sq(delta_Y) + sq(delta_X)); // Longueur droite L² =  △X² + △Y² 
        float delta_x = delta_Y/L;
        float delta_y = delta_X/L;        
            
        int l = 5; //Longeur segment perpendiculaire souhaité  
        //marqueurs
        /*
        if(markersOn && activeFile.fat.size()){
          for (byte i = 0; i < nbrMarkers; i = i + 1) {    
            if(activeFile.markerPointer->markers.Array[i]){
              
              float relativeMarkerPosition = (float)activeFile.markerPointer->markers.Array[i]/(float)activeFile.fat.size();       
              float markerPosition[] = {x1+delta_X*relativeMarkerPosition,y1+delta_Y*relativeMarkerPosition};
                      
              display.drawLine( markerPosition[0]+l*delta_x, markerPosition[1]-l*delta_y, markerPosition[0]-l*delta_x, markerPosition[1]+l*delta_y, WHITE);
              
            }
          }    
        }
        */
        float relativePosition = (float)Player->getFilePosition()/(float)Player->currentTrack.size();
        float filePosition[] = {x1+delta_X*relativePosition,y1+delta_Y*relativePosition};
        
        if (!Player->playingMusic && Player->currentTrack) {   
          
          ecran_->drawCircle(filePosition[0],filePosition[1], 4, BLACK);
          ecran_->drawCircle(filePosition[0],filePosition[1], 3, BLACK);
          ecran_->fillCircle(filePosition[0],filePosition[1], 2, WHITE);
          
        }else if(Player->playingMusic){
          
          //Petit cercle qui indique la direction de jeu
          ecran_->drawCircle(filePosition[0],filePosition[1], 3, WHITE);
          ecran_->fillCircle(filePosition[0],filePosition[1], 2, BLACK);
          ecran_->drawCircle(filePosition[0],filePosition[1], 4, BLACK);
        }
        
      }
  private:
    FdS_Adafruit_VS1053_FilePlayer *Player;
  };
  /**********************
  * PLAYLISTS:
  ***********************/

  class PlaylistDisplay : public Display {
  public:
  private:
  };

  /**********************
  * ACTIONS:
  ***********************/

  class MenuDisplay : public Display {
  public:
  private:
  };

  /**********************
  * METRONOME:
  ***********************/
  class MetronomeDisplay : public Display {
  public:
  private:
  };
  
  /**********************
  * CONTROLER:
  ***********************/
  class DisplayController {
  public:
      Display display;
      FileDisplay files;
      AnalogDisplay analogs;
      PlayingDisplay playing;
      DisplayController(Adafruit_SSD1306 *ecran, FdS_Adafruit_VS1053_FilePlayer *player) :
          display(ecran),
          files(ecran),
          playing(ecran,player),
          analogs(ecran) {
          // Initialisez d'autres instances de classes ici si nécessaire
      }

      void init() {
          display.init();
          // Initialisez d'autres instances de classes ici si nécessaire
      }

      void clear() {
          display.clear();
          // Appelez clear() pour d'autres instances de classes si nécessaire
      }
 
      void show() {
          display.show();
          // Appelez show() pour d'autres instances de classes si nécessaire
      }

      // Ajoutez des fonctions pour accéder à d'autres instances de classes si nécessaire

  private:
      // Ajoutez d'autres instances de classes si nécessaire
  };
#endif