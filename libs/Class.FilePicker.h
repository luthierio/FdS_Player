/**********************
* FILES FUNCTIONS
***********************/
/// File listing helper

#ifndef FilePicker_H   // Vérifie si MACLASSE_H n'a pas été défini
#define FilePicker_H   // Définit MACLASSE_H pour éviter les inclusions multiples

  #include <SdFat.h>

  class FilePicker {
    private:
      SdFat* SD;
      File DIR;
      File FILE; 
    public:
 
      uint8_t dirNum;
      uint8_t fileNum;  
      char dirname[255]; 
      char filename[255];  
      char path[560];

      // Définition du type de fonction de rappel
      typedef void (*CallbackFunction)();

      // Ajout de deux fonctions de rappel
      CallbackFunction onBeforeSelectDir;
      CallbackFunction onAfterSelectDir;
      CallbackFunction onBeforeSelectFile;
      CallbackFunction onAfterSelectFile;

      FilePicker(SdFat *sd) : onBeforeSelectDir(nullptr), onAfterSelectDir(nullptr),
                              onBeforeSelectFile(nullptr), onAfterSelectFile(nullptr) {
        this->SD = sd;
      }

      // Méthodes pour configurer les fonctions de rappel
      void setDirCallbacks(CallbackFunction beforeSelect, CallbackFunction afterSelect) {
        onBeforeSelectDir = beforeSelect;
        onAfterSelectDir = afterSelect;
      }

      void setFileCallbacks(CallbackFunction beforeSelect, CallbackFunction afterSelect) {
        onBeforeSelectFile = beforeSelect;
        onAfterSelectFile = afterSelect;
      }

      void begin(uint8_t dirNum, uint8_t fileNum){        
        selectDir(dirNum);
        selectFile(fileNum);
      }
      void update(){
        selectDir(this->dirNum);
        selectFile(this->fileNum);
      }
      void selectDir(uint8_t num){   

          if (onBeforeSelectDir) {
            onBeforeSelectDir(); // Appel de la fonction de rappel avant la sélection
          }

          this->dirNum = num;      
          this->DIR = getByNum(this->SD->open("/"), num);
          selectFile(this->fileNum);
          updatePath();

          if (onAfterSelectDir) {
            onAfterSelectDir(); // Appel de la fonction de rappel après la sélection
          }
      }   
      void selectFile(uint8_t num){ 

          if (onBeforeSelectFile) {
            onBeforeSelectFile(); // Appel de la fonction de rappel avant la sélection
          }

          this->fileNum = num;   
          this->FILE = getByNum(this->DIR, num);
          updatePath();

          if (onAfterSelectFile) {
            onAfterSelectFile(); // Appel de la fonction de rappel après la sélection
          }
      }  
      
      void updatePath(){
        this->path[0] = '\0';

        if(this->DIR.isDir()){
          
          this->DIR.getName(this->dirname,255);
          strcpy (this->path,"/");
          strcat (this->path,this->dirname);
          strcat (this->path,"/");

          if(this->FILE.getName(this->filename,255) != 0){  
            strcat (this->path,this->filename);
          }else{   
            this->filename[0] = '\0';  
          }
        }else{
          this->dirname[0] = '\0';
          this->filename[0] = '\0';
        }

      }

      File getByNum(File root, uint8_t num) {
        while(true) {

          File entry =  root.openNextFile(O_RDONLY);

          if (! entry) {
            return File();
            break;
          }

          char prefix[2];
          sprintf(prefix, "%02d", num );  

          char name[100]; 
          entry.getName(name,100);

          if ( name[0] == prefix[0]
            && name[1] == prefix[1] ) {        
              return entry;
          }
        }    
        return File();  
      } 
      void print(File dir, int numTabs, Serial_* Serial) {
        while(true) {

          File entry =  dir.openNextFile();
          char dirname[100];

          if (! entry) {
            // no more files
            break;
          }
          for (uint8_t i=0; i<numTabs; i++) {
            Serial->print('\t');
          }
          char filename[100];
          entry.getName(filename,100);

          if (entry.isDirectory()) {
            Serial->print("📁 ");
            Serial->print(filename);
            Serial->println("/");
            this->print(entry, numTabs+1,Serial);
          } else {
            Serial->print(filename);
            // files have sizes, directories do not
            Serial->print("\t\t");
            Serial->println(entry.size(), DEC);
          }
          entry.close();
        }        
      }
  };
#endif
