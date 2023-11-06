/**********************
* FILES FUNCTIONS
***********************/

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
