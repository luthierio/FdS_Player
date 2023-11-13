#ifndef SoundFile_H   // Vérifie si MACLASSE_H n'a pas été défini
#define SoundFile_H   // Définit MACLASSE_H pour éviter les inclusions multiples


  #include <SdFat.h>

  class SoundFile : public File {
    public:
      void ID3() {
      }
      void ID3v2() {
      }
      uint32_t bitrate() {
        return 128000;
      }
  };
  
#endif