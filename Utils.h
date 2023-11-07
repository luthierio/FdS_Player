/**********************
* FILES FUNCTIONS
***********************/
/// File listing helper

void getByNum(File root, char* destination, int num) {  

  while(true) {

    File entry =  root.openNextFile(O_RDONLY);

    if (! entry) {
      break;
    }

    char prefix[2];
    sprintf(prefix, "%02d", num);  

    char name[100];
    entry.getName(name,100);

    if (name[0] == prefix[0]
        && name[1] == prefix[1]) {
        strncpy(destination, name , strlen(name));
        destination[strlen(name)] = '\0';
    }
  }
};

void getFilePathByNum(SdFat SD, char* destination, int dirnum, int filenum) {
    char tempDir[255];
    char tempFile[255];

    getByNum(SD.open("/", O_RDONLY), tempDir, dirnum);
    getByNum(SD.open(tempDir, O_RDONLY), tempFile, filenum);

    strcpy (destination,"/");
    strcat (destination,tempDir);
    strcat (destination,"/");
    strcat (destination,tempFile);

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
