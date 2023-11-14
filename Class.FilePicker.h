/**********************
* FILES FUNCTIONS
***********************/
/// File listing helper

#ifndef FilePicker_H   // Vérifie si MACLASSE_H n'a pas été défini
#define FilePicker_H   // Définit MACLASSE_H pour éviter les inclusions multiples

  #include <SdFat.h>

  class FilePicker {
    public:
  
      SdFat* SD;
      Adafruit_VS1053_FilePlayer* VS1053;
      File DIR;
      File FILE;
      uint8_t * dirNum;
      uint8_t * fileNum;    
      char dirname[255]; 
      char filename[255];  
      char path[560];

      FilePicker(SdFat* sd,Adafruit_VS1053_FilePlayer* VS1053){
        this->SD = sd;
        this->VS1053 = VS1053;
      }
      //Recois deux pointer vers les variables contenant les numéros de sélections
      void begin(uint8_t *dirNum, uint8_t *fileNum){
        this->dirNum = dirNum;
        this->fileNum = fileNum;
        update();
      }
      void update(){
        this->VS1053->pausePlaying(true); 
                
        this->DIR = getByNum(this->SD->open("/"), *this->dirNum);
        delay(1);
        this->FILE = getByNum(this->DIR, *this->fileNum);
        delay(1);

        updatePath();

        this->VS1053->pausePlaying(false);
      }  
      
      void updatePath(){
        this->path[0] = '\0';
        this->DIR.getName(this->dirname,255);
        this->FILE.getName(this->filename,255);
        strcpy (this->path,"/");
        strcat (this->path,this->dirname);
        strcat (this->path,"/");
        strcat (this->path,this->filename);
      }

      File getByNum(File root, uint8_t num) {
        while(true) {

          File entry =  root.openNextFile(O_RDONLY);

          if (! entry) {
            return this->FILE;
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
        return this->FILE;  
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