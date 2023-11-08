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