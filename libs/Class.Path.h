/**********************
* Class Path
***********************/
// Manipulation de chemin de référence vers des chemins de fichier
// Extraction numéros et nom de fichiers...
#ifndef Path_H   // Vérifie si MACLASSE_H n'a pas été défini
#define Path_H   // Définit MACLASSE_H pour éviter les inclusions multiples


  class Path {

    private:
      const char* path;
      const char* SEP = "./";

    public:  
      Path(){}
      Path(const char* path){
        this->path = path;
      }

      const char* get() {
        return this->path;
      }

      const char* suffix() {      
        const char * suffix = strrchr( this->path, '.' );
        if (suffix){        
          return suffix + 1; //+1 to remove leading '.'
        }
        return NULL;
      }
      const char* filename() {  
        const char * filename = strrchr( this->path, '/' );
        if (filename){
          return filename + 1; //+1 to remove leading '/'
        }
        return this->path;      
      }

      void getDirname(char* result, size_t size) {  
        const char * first = strchr( this->path, '/' );
        const char * last = strrchr( this->path, '/' );
        if (first !=  last){    
          size_t length = last - first - 1;  
          strncpy(result, first+1, length);
          result[length] = '\0';
        }else{
          result[0] = '\0';
        }     
      }

      uint8_t getNum(const char * path) {  
        char *output;
        long result = strtol(path, &output, 10);
        return result;
      }
      
      uint8_t fileNum() {        
        return this->getNum(this->filename()); 
      } 
      uint8_t dirNum() {  
        const char * first = strchr( this->path, '/' ) + 1;      
        return this->getNum(first);
      } 

  };
#endif