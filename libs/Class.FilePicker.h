/**********************
* FILES FUNCTIONS
***********************/
/// File listing helper

#ifndef FilePicker_H   // Vérifie si MACLASSE_H n'a pas été défini
#define FilePicker_H   // Définit MACLASSE_H pour éviter les inclusions multiples

  #include <SdFat.h>

  // Constantes pour la longueur des noms de fichier et du chemin
  const int MAX_FILENAME_LENGTH = 255;
  const int MAX_PATH_LENGTH = 560;

  class FilePicker {
    private:
      SdFat* SD;
      File DIR;
    public:
      File FILE; 
      int dirNum;
      int fileNum;  
      char dirname[MAX_FILENAME_LENGTH]; 
      char filename[MAX_FILENAME_LENGTH];  
      char path[MAX_PATH_LENGTH];

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

      void select(uint8_t dirNum, uint8_t fileNum, bool silent = false){      
        if(dirNum < 100 && fileNum < 100){
          selectDir(dirNum,silent);
          selectFile(fileNum,silent);
        }  
      }
      
      void update(){
        selectDir(this->dirNum);
        selectFile(this->fileNum);
      }
        
      void selectDir(uint8_t num, bool silent = false){   

          if (!silent && onBeforeSelectDir) {
            onBeforeSelectDir(); // Appel de la fonction de rappel avant la sélection
          }

          this->dirNum = num;      
          this->DIR = getByNum(this->SD->open("/"), num);
          selectFile(this->fileNum, silent);
          updatePath();

          if (!silent && onAfterSelectDir) {
            onAfterSelectDir(); // Appel de la fonction de rappel après la sélection
          }
      }   
      byte dirExist(){
        return this->dirname[0] != '\0';
      }   
      byte exist(){
        return this->filename[0] != '\0';
      }   
      void selectFile(uint8_t num, bool silent = false){ 

          if (!silent && onBeforeSelectFile) {
            onBeforeSelectFile(); // Appel de la fonction de rappel avant la sélection
          }

          this->fileNum = num;   
          this->FILE = getByNum(this->DIR, num);
          updatePath();

          if (!silent && onAfterSelectFile) {
            onAfterSelectFile(); // Appel de la fonction de rappel après la sélection
          }
      }  
      
      uint32_t getSize(){   
        return FILE.size();
      }   
      void updatePath(){
        memset(this->path, 0, MAX_PATH_LENGTH);

        if(this->DIR.isDir()){
          
          this->DIR.getName(this->dirname, MAX_FILENAME_LENGTH);
          strcpy (this->path,"/");
          strcat (this->path,this->dirname);
          strcat (this->path,"/");

          if(this->FILE.getName(this->filename, MAX_FILENAME_LENGTH) != 0){  
            strcat (this->path,this->filename);
          }else{   
            memset(this->filename, 0, MAX_FILENAME_LENGTH);
          }
        }else{
          memset(this->dirname, 0, MAX_FILENAME_LENGTH);
          memset(this->filename, 0, MAX_FILENAME_LENGTH);
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
          entry.getName(name, 100);

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
          entry.getName(filename, 100);

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

