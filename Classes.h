
#include "Arduino.h"
#include <SdFat.h>

class Path {

  private:
    const char* path;

  public:  
    Path(){}
    Path(const char* path){
      this->path = path;
    }

    //recois un pointer!
    void print() {
    }

    const char* get() {
      return this->path;
    }
    const char* set(const char* path) {
      this->path = path;
      return this->path;
    }
    
    const char* join(const char* path) {
      return this->path;
    }

    const char* filename() {
      return this->path;
    }
    const char* dirname() {
      return this->path;
    }
    const char* suffix() {
      return this->path;
    }
    const char* stem() {
      return this->path;
    }
    const char* root() {
      return this->path;
    }
    const char* parent() {
      return this->path;
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