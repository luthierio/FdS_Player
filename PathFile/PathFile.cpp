#include "Arduino.h"
#include "PathFile.h"
#include <SdFat.h>

PathFile::PathFile(const char* path): FatFile(const char* path)  {
  this->fullPath = path;
};

void PathFile::rename(const char* path) {
  this->fullPath = path;
	FatFile::rename(path);
};
