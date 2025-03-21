
#ifndef Display_H   // Vérifie si MACLASSE_H n'a pas été défini
#define Display_H   // Définit MACLASSE_H pour éviter les inclusions multiples

  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>

  #include "./Class.UTF8Converter.h"
  UTF8Converter UTF8;

  /**********************
  * MAIN Class:
  ***********************/
  class Display {
  public:
      Display(Adafruit_SSD1306 *ecran) : ecran_(ecran) {}

      void init() {
          ecran_->clearDisplay();
          ecran_->display();
          ecran_->setTextSize(1);
          ecran_->setTextWrap(false);
          ecran_->setTextColor(SSD1306_WHITE);
          ecran_->cp437(true);
      }

      void clear() {
        ecran_->clearDisplay();
        ecran_->display();
      }

      void show() {
          ecran_->display();
      }
      void logo() {
        ecran_->drawBitmap (0,0, LOGO_128x64, 128,64, 1); 
        ecran_->display();
      }
      void message(const char *texte = nullptr) {
        ecran_->fillRect(0, 52, 128, 32, BLACK); 
        //ecran_->drawFastHLine(0, 52, 128, WHITE);
        drawCentreString(texte, 64, 60);
        ecran_->display();
      }
      void message(const __FlashStringHelper *texte= nullptr) {
        ecran_->fillRect(0, 52, 128, 32, BLACK); 
        //ecran_->drawFastHLine(0, 52, 128, WHITE);
        drawCentreString(texte, 64, 60);
        ecran_->display();
      }
      void error(const __FlashStringHelper *texte = nullptr) {

        ecran_->clearDisplay();
        ecran_->setTextSize(1);
        ecran_->setTextColor(WHITE);
        ecran_->setCursor(0, 10);
        
        ecran_->drawCircle(128/2, 64/2-4, 18, WHITE);
        ecran_->drawFastHLine(128/2-8, 36, 16, WHITE);
        ecran_->drawFastHLine(128/2-8, 37, 16, WHITE);
        ecran_->drawBitmap (128/2-6-4, 20, smallCross, 8,8, WHITE); 
        ecran_->drawBitmap (128/2+6-4, 20, smallCross, 8,8, WHITE);   
        message((char*)texte);
        ecran_->display();
      }
      void confirm() {
        ecran_->drawBitmap (0,0, LOGO_128x64, 128,64, 1); 
        //ecran_->display();
      }
      void cleanZone(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color = BLACK){  
        ecran_->fillRect(x ,y , w, h,  color);
      }

      // Afficher un texte
      void printTxtNum(const int num, uint8_t x = 0, uint8_t y = 0, const GFXfont *font = NULL, uint8_t tailleTexte = 1, bool color = WHITE) {

        char txtNum[2];
        sprintf(txtNum, "%02d", num);  
        if(num < 10 ){
          txtNum[0] = ' ';
        }
        printTxt(txtNum,x,y,font, tailleTexte,color);
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
        ecran_->print(texte);
      }

      void printTxt(const __FlashStringHelper *texte, uint8_t x = 0, uint8_t y = 0, const GFXfont *font = NULL, uint8_t tailleTexte = 1, bool color = WHITE) {

        int16_t  x1, y1;
        uint16_t w, h;
        
        ecran_->setFont(font);
        ecran_->setTextColor(color);
        ecran_->setTextSize(tailleTexte);
        ecran_->setCursor(x, y);
        ecran_->print(texte);
      }

      void drawCentreString(const char *texte, int x, int y, const GFXfont *font = NULL, uint8_t tailleTexte = 1)
      {
          int16_t x1, y1;
          uint16_t w, h;
          ecran_->setFont(font);
          ecran_->setTextSize(tailleTexte);
          ecran_->getTextBounds(texte, x, y, &x1, &y1, &w, &h); //calc width of new string
          ecran_->setCursor(x - w / 2, y - h / 2);
          ecran_->print(texte);
      }
      void drawCentreString(const __FlashStringHelper *texte, int x, int y, const GFXfont *font = NULL, uint8_t tailleTexte = 1)
      {
          drawCentreString(reinterpret_cast<const char*>(texte), x, y, font, tailleTexte);
      }
      void fillVHatch(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h){
          for (byte i = 0; i < w/4 ; i = i + 1) {
            ecran_->drawFastVLine(x0 + i*4, y0, h, WHITE);
          }
      }

      void basename(char* filename){
        const char toClip[] = {'.', '['};
        deleteAfterChars(filename, toClip);
      } 

      void deleteAfterChar(char* texte, char caractere) {
          for (int i = 0; i < strlen(texte); i++) {
              if (texte[i] == caractere) {
                  texte[i] = '\0'; // Remplace le caractère trouvé par le caractère nul pour terminer la chaîne.
                  break; // Sort de la boucle dès qu'on trouve le caractère.
              }
          }
      }
      void deleteAfterChars(char* texte, const char* caracteres) {
          for (int i = 0; i < strlen(texte); i++) {
              for (int j = 0; j < strlen(caracteres); j++) {
                  if (texte[i] == caracteres[j]) {
                      texte[i] = '\0'; // Remplace le caractère trouvé par le caractère nul pour terminer la chaîne.
                      return; // Sort de la fonction dès qu'on trouve l'un des caractères.
                  }
              }
          }
      }
      

  protected:
      Adafruit_SSD1306 *ecran_;
  };

  /**********************
  * FICHIERS:
  ***********************/
  class FileDisplay : public Display {
  public:
      FileDisplay(
          Adafruit_SSD1306 *ecran, 
          FilePicker *filePicker, 
          MP3File *mp3) :
        Display(ecran),
        filePicker (filePicker),
        mp3 (mp3){}

      // TOTO use filePicker & MP3 from instance
      void show() {
        printPath();
      }

      void printPath() {
        
        //On efface la zone   
        ecran_->fillRect(0, 0, 100, 16, BLACK); 
        ecran_->fillRect(0, 16, 128, 35, BLACK); 


        if(!filePicker->dirExist()){

          ecran_->drawBitmap (2, 32, folderIcon16, 16, 16 ,WHITE);
          printTxtNum(filePicker->dirNum, 30, 48, &FreeSans12pt7b); 
          printTxt(F("/"), 64, 48, &FreeSans12pt7b); 
          printTxtNum(filePicker->fileNum, 80, 48, &FreeSans12pt7b); 

        }else{

          printDirPath(0, 3);

          if (!filePicker->exist()) {
            printTxtNum(filePicker->fileNum, 48, 48, &FreeSans18pt7b);             
          }else{
            /*
            if(mp3->hasID3V1){
              printID3(0, 32, &FreeSerif9pt7b);
            }else{
              printFilePath(0, 32, &FreeSerif9pt7b);
            }
            */
            printFilePath(0, 32, &FreeSerif9pt7b);
          }

        } 

      }

      void printDirPath(int x, int y, const GFXfont *font = NULL, uint8_t textSize = 1){
        
          ecran_->drawBitmap (x, y, folderIcon8, 8,8,WHITE);
          printTxt(UTF8.convertToASCII(filePicker->dirname+3), x+12, y);

      }
      
      void printID3(int x, int y, const GFXfont *font = NULL, uint8_t textSize = 1) {

          printTxt(UTF8.convertToASCII(mp3->ID3V1.title), x, y, font, textSize);

          int shift = 0;
          if (strlen(mp3->ID3V1.year) != 0){
            printTxt(mp3->ID3V1.year, x, y + 10, NULL, textSize);
            printTxt(F("/"), x+29, y + 10, NULL, textSize);
            shift = 38;
          }

          if (strlen(mp3->ID3V1.comment) != 0){
            printTxt(UTF8.convertToASCII(mp3->ID3V1.comment), x+shift, y + 10, NULL, textSize);
          }else{
            printTxt(UTF8.convertToASCII(mp3->ID3V1.album), x+shift, y + 10, NULL, textSize);
          }
      }
      void printFilePath(int x, int y, const GFXfont *font = NULL, uint8_t textSize = 1) {

          char displayedFile[255]; // Assurez-vous que la taille est suffisamment grande
          char fileInfos[255]; // Assurez-vous que la taille est suffisamment grande
          fileInfos[0] = '\0';
          strcpy(displayedFile, filePicker->filename + 3); // Copie à partir du 4ème caractère
          displayedFile[strcspn(displayedFile, ".")] = '\0'; // Ajoute un caractère de fin de chaîne à la position du point
          const char *startBracket = strchr(displayedFile, '[');
          if (startBracket != NULL) {
            displayedFile[strcspn(displayedFile, "[")] = '\0'; // Ajoute un caractère de fin de chaîne à la position du point
            getBracketContent(filePicker->filename, fileInfos, sizeof(fileInfos));
          }

          printTxt(UTF8.convertToASCII(displayedFile), x, y, font, textSize);
          printTxt(UTF8.convertToASCII(fileInfos), x, y + 10, NULL, textSize);
          
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

  protected:
      FilePicker *filePicker;
      MP3File *mp3;
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
        
        if ( VUsb > VUSB_PLUGGED) {
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
      PlayingDisplay(Adafruit_SSD1306 *ecran, FdS_Adafruit_VS1053_FilePlayer *player, FilePicker *filePicker, t_state *state, audioDataManager *datas) : 
        Display(ecran),
        Player (player),
        filePicker (filePicker),
        datas (datas),
        state (state){}

      void fullProgressBar(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t L, uint8_t pitchSpaceWidth){   

        if(filePicker->exist() &&  datas->hasData() && datas->getPitchStep() != 5){
          pitch(x2-pitchSpaceWidth + 2  , y2-L/2 , L , L ); 
          progressBar(x1, y1, x2-pitchSpaceWidth, y2, true);
          playMode(x2-pitchSpaceWidth, y2); 

        }else if(filePicker->exist()){

          progressBar(x1, y1, x2, y2, true);
          playMode(x2, y2); 

        }  

      }
      void playMode(uint8_t x, uint8_t y){   
        if(state->playMode == AUTO){

          ecran_->fillTriangle(x-8,y-4, x-8,y+4, x-4,y, WHITE);

        }else if(state->playMode == RANDOM){              

          ecran_->fillTriangle(x-12,y-4, x-12,y+4, x-8,y, WHITE);
          ecran_->fillTriangle(x-4,y-4, x-4,y+4, x-8,y, WHITE);

        }else if(state->playMode == REPEATONE){

          ecran_->fillTriangle(x-4,y-4, x-4,y+4, x-8,y, WHITE);

        }
      }
      void progressBar(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool disPlayMarkers = false){  
        
        int l = 6; //Longeur segment perpendiculaire souhaité  
        int playingSize = Player->currentTrack.size();
        int pickedSize = filePicker->getSize();
        
        ecran_->drawLine(x1,y1,x2,y2, WHITE);
        ecran_->fillCircle(x1,y1, 2, WHITE);
        ecran_->fillCircle(x2,y2, 2, WHITE);
        
        int delta_X = x2-x1; //Delta X
        int delta_Y = y2-y1; //Delta Y
          
          
        float L = sqrt(sq(delta_Y) + sq(delta_X)); // Longueur droite L² =  △X² + △Y² 
        float delta_x = delta_Y/L;
        float delta_y = delta_X/L;        
            

        //marqueurs
        //Test pour voir si il y a des marqueurs sur le fichier actuel
        if(disPlayMarkers && pickedSize){
          uint32_t* markersArray = datas->getMarkers();

          for (byte i = 0; i < datas->getMarkerCount(); i = ++i) {  
            float relativeMarkerPosition = (float)markersArray[i]/(float)pickedSize;       
            float markerPosition[] = {x1+delta_X*relativeMarkerPosition,y1+delta_Y*relativeMarkerPosition};
                    
            ecran_->drawLine( markerPosition[0]+l*delta_x, markerPosition[1]-l*delta_y, markerPosition[0]-l*delta_x, markerPosition[1]+l*delta_y, WHITE);
          }

        }
        
        //Test pour voir si l'on est actuellement en train de jouer la poste dont la barre s'affiche
        if(playingSize == pickedSize){
          //Petit cercle qui indique la direction de jeu
          float relativePosition = (float)Player->getFilePosition()/(float)pickedSize;
          float filePosition[] = {x1+delta_X*relativePosition,y1+delta_Y*relativePosition};
          if (!Player->playingMusic && Player->currentTrack) {  
            ecran_->drawCircle(filePosition[0],filePosition[1], 4, BLACK);
            ecran_->drawCircle(filePosition[0],filePosition[1], 3, BLACK);
            ecran_->fillCircle(filePosition[0],filePosition[1], 2, WHITE);
            
          }else if(Player->playingMusic){
            
            ecran_->drawCircle(filePosition[0],filePosition[1], 3, WHITE);
            ecran_->fillCircle(filePosition[0],filePosition[1], 2, BLACK);
            ecran_->drawCircle(filePosition[0],filePosition[1], 4, BLACK);
          }

        }
        
        
      }
        
      void pitch(uint8_t x, uint8_t y, uint8_t w, uint8_t h){  
        ecran_->fillRect(x,y, w, h, BLACK);
        pitchSymbol(x + 2  , y , w , h);            
        pitchValue (x + 12+4 , y+2 );  
      }
      void pitchSymbol(uint8_t x, uint8_t y, uint8_t w, uint8_t h){  
        
        if(datas->getPitchMode()){   
          //Pitch mode SPeed
            ecran_->drawLine    ( x     , y+2   , x     , y+h-2 , WHITE );   // Ligne V 1
            ecran_->drawLine    ( x     , y+h/2 , x+w   , y+h/2 , WHITE );   // Ligne H
            ecran_->drawLine    ( x+w   , y+2   , x+w   , y+h-2 , WHITE );   // Ligne V 2 
          
          if(datas->getPitchStep() > 5){   
                        
            ecran_->fillTriangle( x     , y+2   , x     , y+h-2 , x+w   , y+h/2 , WHITE);
            
          }else if(datas->getPitchStep() < 5){
            
            ecran_->fillTriangle(x+w   , y+2   , x+w    , y+h-2 , x     , y+h/2 , WHITE);
            
          }
          
        }else{
          ecran_->drawLine      ( x+2   , y     , x+w-2 , y     , WHITE );   // Ligne H 1
          ecran_->drawLine      ( x+w/2 , y     , x+w/2 , y+h   , WHITE );   // Ligne V
          ecran_->drawLine      ( x+2   , y+h   , x+w-2 , y+h   , WHITE );   // Ligne H 2     
          
          if(datas->getPitchStep() > 5){  
            
            ecran_->fillTriangle( x+2   , y+h   , x+w-2 , y+h , x+w/2 , y , WHITE);
            
          }else if(datas->getPitchStep() < 5){
            
            ecran_->fillTriangle( x+2   , y     , x+w-2 , y   , x+w/2 , y+h-2 , WHITE);
            
          }
          
        }

      }

      void pitchValue(uint8_t x, uint8_t y){  

        ecran_->setCursor(x, y); 
        
        ecran_->setFont();
        ecran_->setTextSize(1);
        
        ecran_->print(abs(datas->getPitchStep()-5));
        
      }
  private:
    FdS_Adafruit_VS1053_FilePlayer *Player;
    FilePicker *filePicker;
    audioDataManager *datas;
    t_state *state;
  };
  /**********************
  * PITCH:
  ***********************/

  class PitcherDisplay : public Display {
  public:
      PitcherDisplay(Adafruit_SSD1306 *ecran, audioDataManager *datas) : 
        Display(ecran),
        datas (datas){}


  private:
    audioDataManager *datas;
  };
  /**********************
  * PLAYLISTS:
  ***********************/

  class PlaylistsDisplay : public Display {
  public:
      PlaylistsDisplay(Adafruit_SSD1306 *ecran, PlaylistManager *playlists, t_state *state) : 
        Display(ecran),
        playlists (playlists),
        state (state){}

      void show(){
        //ecran_->clearDisplay();
        printNav();
        printList();
        ecran_->display();
      }
      void loop(){  
        playing(); 
      }
      void printNav(uint8_t x = 0){   
        ecran_->fillRect(0,0, 10, 64, BLACK);
        int plHeight = 64/playlists->size;
        for (byte i = 0; i < playlists->size; i = i + 1) {  
          if(playlists->getPosition() == i){
            ecran_->drawCircle(x+3, plHeight/2 + i*plHeight, 3, WHITE); 
          }else{
            ecran_->fillCircle(x+3, plHeight/2 + i*plHeight, 1, WHITE); 
          }
        }
        //ecran_->display();
      }
      void printList(){
        ecran_->fillRect(10,0, 128-20, 64, BLACK); 
        items(10);
        mode(24); 
      }
      void playing(){  
        uint8_t x = 10;
        //Le fichier qui est sélectionné dans le player est celui ci
        if(state->dirNum == playlists->currentPlaylist->currentItem->dirNum && state->fileNum == playlists->currentPlaylist->currentItem->fileNum ){

          ecran_->fillTriangle( x,14    , x,14+4  , x+6 , 14 , WHITE);
          ecran_->fillTriangle( x,50    , x,50-4  , x+6 , 50 , WHITE);
          //ecran_->fillTriangle( 10, SCREEN_HEIGHT/2-2 , 10, SCREEN_HEIGHT/2+2, 10+2,SCREEN_HEIGHT/2, WHITE);      // Triangles forward
        }
      }
      void mode(uint8_t x){

        if(state->playlistMode == RANDOM){
          ecran_->fillTriangle( x-6,14    , x,14-4  , x+6 , 14 , WHITE);      // Triangle haut vers le haut
        }
        if(state->playlistMode == AUTO || state->playlistMode == RANDOM){
          ecran_->fillTriangle( x-6,50    , x,50+4  , x+6 , 50 , WHITE);      // Triangle bas vers le bas
        }  
        if(state->playlistMode == REPEATONE){
          ecran_->fillTriangle( x-6,50    , x,50-4  , x+6 , 50 , WHITE);  // Triangle bas vers le haut
        } 

      }
      void items(uint8_t x){  

        uint8_t position = playlists->getPlayPosition();

        PlaylistItem item =  playlists->currentPlaylist->getItem(); //Position courante
        PlaylistItem prevItem =  playlists->currentPlaylist->getItem(position-1);
        PlaylistItem nextItem =  playlists->currentPlaylist->getItem(position+1);

        basename(item.fileName);

        printTxt(item.dirName, x+24,18, NULL, 0);
        printTxt(item.fileName+3, x+24, 42, &FreeSerif9pt7b);

        ecran_->drawFastHLine(x, 14, SCREEN_WIDTH-10*2, WHITE);
        ecran_->drawFastHLine(x, 50, SCREEN_WIDTH-10*2, WHITE);
        
        printTxtNum(position+1, x, SCREEN_HEIGHT/2+4, &FreeSans9pt7b); 

        if(position == 0){

          fillVHatch(x+2,  0, SCREEN_WIDTH-10*2, 14);
          
        }else if(!prevItem.isEmpty()){          

          basename(prevItem.fileName);
          printTxt(prevItem.fileName+3, x+24,2, NULL, 0);

        }

        if(position+1 == playlists->currentPlaylist->size ){

          fillVHatch(x+2, 50, SCREEN_WIDTH-10*2, 14);

        }else if(!nextItem.isEmpty()){     

          basename(nextItem.fileName);
          printTxt(nextItem.fileName+3, x+24,54, NULL, 0);

        }

      }

  private:
    PlaylistManager *playlists;
    t_state *state;
  };

  /**********************
  * PROMPT_IDS:
  ***********************/

  class PromptDisplay : public Display {
  public:
      PromptDisplay(Adafruit_SSD1306 *ecran) : Display(ecran){

      }

      void show(uint8_t prompt_ID, bool confirm){  

        ecran_->clearDisplay();        
        ecran_->drawFastHLine(0, 24, 128, WHITE);

        if       (prompt_ID == PL_IMPORT) {
          drawCentreString(F("Import M3U"), 64, 22, &FreeSerif9pt7b);
        }else if (prompt_ID == PL_EXPORT) {
          drawCentreString(F("Export M3U"), 64, 22, &FreeSerif9pt7b);
        }else if (prompt_ID == PL_ADD) {
          drawCentreString(F("Add to Playlist"), 64, 22, &FreeSerif9pt7b);
        }

        drawCentreString(F("Confirm ?"), 128/2, 36);
        if(confirm){
          drawCentreString(F("Yes"), 128/2, 64, &FreeSerif9pt7b);
        }else {
          drawCentreString(F("No"), 128/2, 64, &FreeSerif9pt7b);

        }  
      }
  private:
  };

  /**********************
  * METRONOME:
  ***********************/
  class MetronomeDisplay : public Display {
  public:
      MetronomeDisplay(Adafruit_SSD1306 *ecran, Metronome *metronome) : 
        Display(ecran),
        metronome (metronome){}
      void show(){
        graphics();
        bpm();
        beats();
      }
      void graphics(){
        ecran_->fillCircle(64,26, 22, BLACK);
        ecran_->drawCircle(64,26, 22, WHITE);
        ecran_->setFont();
        ecran_->setCursor(64-8,26+10);
        ecran_->print("BPM");   
      }
      void bpm(){
              
        ecran_->fillRect(64-12,26-14, 26, 16, BLACK); 
        
        ecran_->setFont(&FreeSerif9pt7b);

        if(metronome->getBpm() < 100){    
          ecran_->setCursor(64-8, 26);
        }else{
          ecran_->setCursor(64-14, 26);    
        }
        ecran_->print(metronome->getBpm()); 

      }
      void beats(){
        ecran_->fillRect(0,50, 128, 14, BLACK); 
        
        int BeatWidth = 128/metronome->getBeatsPerBar();
        for (byte i = 0; i < metronome->getBeatsPerBar(); i = i + 1) {   
          if(metronome->getBeatCount() == i){
              ecran_->fillCircle(BeatWidth/2 + i*BeatWidth,60, 6, WHITE);
          }else{
              ecran_->fillCircle(BeatWidth/2 + i*BeatWidth,60, 2, WHITE); 
          }
        }
      }
  private:
    Metronome *metronome;
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
      PitcherDisplay pitcher;
      PlaylistsDisplay playlists;
      MetronomeDisplay metronome;
      PromptDisplay menu;
      DisplayController(
            Adafruit_SSD1306 *ecran, 
            FdS_Adafruit_VS1053_FilePlayer *player, 
            FilePicker *filePicker, 
            Pitcher *pitcher, 
            PlaylistManager *playlists, 
            t_state *state, 
            audioDataManager *datas,
            MP3File *mp3,
            Metronome *metronome
            ) :
          display(ecran),
          files(ecran,filePicker, mp3),
          playing(ecran,player,filePicker,state, datas),
          pitcher(ecran,datas),
          playlists(ecran,playlists,state),
          metronome(ecran,metronome),
          menu(ecran) ,
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