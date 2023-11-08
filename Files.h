/**********************
* FILES FUNCTIONS
***********************/
/// File listing helper

class FileManager {
  public:
    SdFat* SD;
    FileManager(SdFat* SD){
      this->SD = SD;
    }
    void ID3() {
    }
    void ID3v2() {
    }
    uint32_t bitrate() {
      return 128000;
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
