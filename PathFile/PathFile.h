#ifndef PathFile_h
#define PathFile_h

#include "Arduino.h"
#include <SdFat.h>

class PathFile: public FatFile
{
  private:
  
  public:
    PathFile(const char* path);
    const char* fullPath;
    void rename(const char* path);
    // other custom methods
};


#endif
