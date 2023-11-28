/**********************
* FILES FUNCTIONS
***********************/
/// File listing helper

#ifndef FilePicker_H   // Vérifie si MACLASSE_H n'a pas été défini
#define FilePicker_H   // Définit MACLASSE_H pour éviter les inclusions multiples

  #include <SdFat.h>

#ifndef MAX_FILENAME_LENGTH
  #define  MAX_FILENAME_LENGTH 255
#endif

#ifndef MAX_DIRNAME_LENGTH
  #define  MAX_DIRNAME_LENGTH 255
#endif

#ifndef MAX_PATH_LENGTH
  #define MAX_PATH_LENGTH 560
#endif

#ifndef MIN_DIR_NUM
  #define MIN_DIR_NUM 0 // OLED display width, in pixels
#endif

#ifndef MAX_DIR_NUM
  #define MAX_DIR_NUM 99 // OLED display width, in pixels
#endif

#ifndef MIN_DIR_NUM
  #define MIN_DIR_NUM 0 // OLED display width, in pixels
#endif

#ifndef MAX_FILES_NUM
  #define MAX_FILES_NUM 99 // OLED display width, in pixels
#endif


  enum FileType {
      FILE_ONLY,
      DIR_ONLY,
      FILE_AND_DIR
  };

  class FilePicker {
    private:
      File DIR;
    public:
      SdFat* SD;
      File FILE; 
      int8_t dirNum;
      int8_t fileNum;  
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
        if(dirNum <= MAX_DIR_NUM && fileNum <= MAX_FILES_NUM){
          selectDir(dirNum,silent);
          selectFile(fileNum,silent);
        }  
      }
              
      void selectDir(uint8_t num, bool silent = false){   

          if (!silent && onBeforeSelectDir) {
            onBeforeSelectDir(); // Appel de la fonction de rappel avant la sélection
          }
          resetFile();
          this->dirNum = num;      
          this->DIR = getByNum(this->SD->open("/"), num, DIR_ONLY);
          updatePath();

          if (!silent && onAfterSelectDir) {
            onAfterSelectDir(); // Appel de la fonction de rappel après la sélection
          }
      }  
      
      void resetFile(){
        this->fileNum = -1;     
        this->FILE = File();
      }
      void selectFile(uint8_t num, bool silent = false){ 

          if (!silent && onBeforeSelectFile) {
            onBeforeSelectFile(); // Appel de la fonction de rappel avant la sélection
          }

          this->fileNum = num;   
          this->FILE = getByNum(this->DIR, num, FILE_ONLY);
          updatePath();

          if (!silent && onAfterSelectFile) {
            onAfterSelectFile(); // Appel de la fonction de rappel après la sélection
          }
      }   

      byte dirExist(){
        return this->dirname[0] != '\0';
      }   
      byte exist(){
        return this->filename[0] != '\0';
      }   
      
      uint32_t getSize(){   
        return FILE.size();
      }   
      void resetPath(){

        memset(this->dirname, 0, MAX_DIRNAME_LENGTH);
        memset(this->filename, 0, MAX_FILENAME_LENGTH);
        memset(this->path, 0, MAX_PATH_LENGTH);
      }
      void updatePath(){

        resetPath();
        
        if(this->DIR.isDir()){
          
          this->DIR.getName(this->dirname, MAX_FILENAME_LENGTH);
          strcpy (this->path,"/");
          strcat (this->path,this->dirname);
          strcat (this->path,"/");

          if(this->FILE.getName(this->filename, MAX_FILENAME_LENGTH) != 0){  
            strcat (this->path,this->filename);
          }
          
        }
      }

      bool getNumsFromPath(const char* link, int8_t& dirNum, int8_t& fileNum) {
        // Extraire le dirNum (deux premiers caractères)
        char dirNumStr[3];
        strncpy(dirNumStr, link, 2);
        dirNumStr[2] = '\0';
        
        // Vérifier si les caractères extraits sont des chiffres
        if (isdigit(dirNumStr[0]) && isdigit(dirNumStr[1])) {
          dirNum = atoi(dirNumStr);
        } else {
          dirNum = -1;  // Valeur par défaut en cas d'erreur
          return false;
        }

        // Trouver la première occurrence de '/'
        const char* firstSlash = strchr(link, '/');

        // Extraire le fileNum (deux caractères après la première occurrence de '/')
        char fileNumStr[3];
        strncpy(fileNumStr, firstSlash + 1, 2);
        fileNumStr[2] = '\0';

        // Vérifier si les caractères extraits sont des chiffres
        if (isdigit(fileNumStr[0]) && isdigit(fileNumStr[1])) {
          fileNum = atoi(fileNumStr);
        } else {          
          fileNum = -1;  // Valeur par défaut en cas d'erreur
          return false;
        }        
        return true;
      }
      bool isPlaying(FdS_Adafruit_VS1053_FilePlayer *player) {
        return (player->currentTrack.size() == getSize());
      }

      File getByNum(File root, uint8_t num, FileType fileType, const char* fileExtension = nullptr) {
          
          while (true) {
              File entry = root.openNextFile(O_RDONLY);

              if (!entry) {
                  return File();
                  break;
              }

              char prefix[3]; // Ajout d'un élément pour le caractère nul '\0'
              snprintf(prefix, sizeof(prefix), "%02d", num);

              char name[100];
              entry.getName(name, sizeof(name));

              if (name[0] == prefix[0] && name[1] == prefix[1]) {
                  if ((fileType == FILE_ONLY && entry.isDirectory()) ||
                      (fileType == DIR_ONLY && !entry.isDirectory())) {
                      // Si le type de fichier ne correspond pas à ce qui est demandé, on ignore cette entrée
                      entry.close();
                      continue;
                  }

                  if (fileType == FILE_ONLY && fileExtension != nullptr) {
                      // Si une extension est spécifiée et que le fichier ne se termine pas par cette extension, on ignore cette entrée
                      size_t entryNameLen = strlen(name);
                      size_t extensionLen = strlen(fileExtension);
                      
                      if (entryNameLen >= extensionLen) {
                          const char* entryExtension = name + entryNameLen - extensionLen;
                          if (strcmp(entryExtension, fileExtension) != 0) {
                              entry.close();
                              continue;
                          }
                      }
                  }
                  return entry;
              }
              entry.close();
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
            Serial->print(F("📁 "));
            Serial->print(filename);
            Serial->println(F("/"));
            this->print(entry, numTabs+1,Serial);
          } else {
            Serial->print(filename);
            // files have sizes, directories do not
            Serial->print(F("\t\t"));
            Serial->println(entry.size(), DEC);
          }
          entry.close();
        }        
      }
  };
#endif

