/**********************
* FILES FUNCTIONS
***********************/
/// File listing helper
#include <SdFat.h>

class FilePicker {
  public:

    SdFat* SD;
    File DIR;
    File FILE;
    uint8_t * dirNum;
    uint8_t * fileNum;    
    char dirname[255]; 
    char filename[255];  
    char path[560];

    FilePicker(SdFat* sd){
      this->SD = sd;
    }
    //Recois deux pointer vers les variables contenant les numéros de sélections
    void begin(uint8_t *dirNum, uint8_t *fileNum){
      this->dirNum = dirNum;
      this->fileNum = fileNum;
    }
    void update(){
      delay(1);
      this->DIR = getByNum(this->SD->open("/"), *this->dirNum);
      delay(1);
      this->FILE = getByNum(this->DIR, *this->fileNum);
      updatePath();
      delay(10);
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

File getFileByNum(File root, int num) {  

  while(true) {

    File entry =  root.openNextFile(O_RDONLY);

    if (! entry) {
      break;
    }

    char prefix[2];
    sprintf(prefix, "%02d", num);  

    char name[100]; 
    entry.getName(name,100);

    if ( name[0] == prefix[0]
      && name[1] == prefix[1] ) {        
        return entry;
    }
  }

  return root;

};

boolean getFilePathByNum(SdFat SD, char* path, const int dirnum, const int filenum) {    
    File root = SD.open("/", O_RDONLY);
    File aDir = getFileByNum(root, dirnum);
    if(aDir.isDir()){
      File aFile = getFileByNum(aDir, filenum);      
      if(aFile.isFile()){
        char filename[255];
        char dirname[255];
        if(aDir.getName(dirname,255) && aFile.getName(filename,255)){
          strcpy (path,"/");
          strcat (path,dirname);
          strcat (path,"/");
          strcat (path,filename);
          return true;
        }
      }
    }
    return false;
}
/// File listing helper
void printDirectory(File dir, int numTabs) {
   while(true) {

     File entry =  dir.openNextFile();
     char dirname[100];

     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     char filename[100];
     entry.getName(filename,100);

     if (entry.isDirectory()) {
      Serial.print("📁 ");
      Serial.print(filename);
      Serial.println("/");
      printDirectory(entry, numTabs+1);
     } else {
       Serial.print(filename);
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
