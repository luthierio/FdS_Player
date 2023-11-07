
#include "Arduino.h"
#include <SdFat.h>


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
      return (char*)this->path;
    }

    const char* join(const char* path) {
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

class SoundFile : public File {
  public:
    void ID3() {
    }
    void ID3v2() {
    }
    void bitrate() {
    }
};

class PathFile : public File {
  private:
    const char* path;
  public:
    PathFile() {}
    /** Create an open SdFile.
    * \param[in] path path for file.
    * \param[in] oflag open flags.
    */
    PathFile(const char* path) {
      this->path = path;  
      File::open(path);  
    }
    PathFile(const char* path, oflag_t oflag) {
      this->path = path;  
      File::open(path,oflag);  
    }

    void open(const char* path) {
      this->path = path;
      File::open(path);
    }
    void open(const char* path, oflag_t oflag) {
      this->path = path;
      File::open(path,oflag);
    }

    void rename(const char* path) {
      this->path = path;
      File::rename(path);
    }

    const char* getPath() {
      return this->path;
    }
    void ID3() {
    }
    void ID3v2() {
    }
    void bitrate() {
    }
};