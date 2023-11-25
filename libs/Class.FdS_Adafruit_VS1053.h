// FdS_Adafruit_VS1053.h
#ifndef FDS_ADAFRUIT_VS1053_H
#define FDS_ADAFRUIT_VS1053_H

#include <Adafruit_VS1053.h>
#define VS1053_PARAM_PLAYSPEED 0x1E04
#define VS1053_PARAM_BITRATE 0x1E05


class FdS_Adafruit_VS1053_FilePlayer : public Adafruit_VS1053_FilePlayer {
public:
  FdS_Adafruit_VS1053_FilePlayer(int8_t rst, int8_t cs, int8_t dcs, int8_t dreq, int8_t cardcs);
  FdS_Adafruit_VS1053_FilePlayer(int8_t cs, int8_t dcs, int8_t dreq, int8_t cardcs);
  FdS_Adafruit_VS1053_FilePlayer(int8_t mosi, int8_t miso, int8_t clk, int8_t rst, int8_t cs, int8_t dcs, int8_t dreq, int8_t cardcs);

  uint16_t getVS1053BitRate();
  //void getMP3BitRate();
  void setPlaySpeed(uint16_t data);
  uint32_t getFilePosition();
  boolean jumpTo(uint32_t startPosition);
  boolean verifyPatch(const uint16_t *patch, uint16_t patchsize);
};

// Implémentation en ligne
inline FdS_Adafruit_VS1053_FilePlayer::FdS_Adafruit_VS1053_FilePlayer(int8_t rst, int8_t cs, int8_t dcs, int8_t dreq, int8_t cardcs)
    : Adafruit_VS1053_FilePlayer(rst, cs, dcs, dreq, cardcs) {
}

inline FdS_Adafruit_VS1053_FilePlayer::FdS_Adafruit_VS1053_FilePlayer(int8_t cs, int8_t dcs, int8_t dreq, int8_t cardcs)
    : Adafruit_VS1053_FilePlayer(cs, dcs, dreq, cardcs) {
}

inline FdS_Adafruit_VS1053_FilePlayer::FdS_Adafruit_VS1053_FilePlayer(int8_t mosi, int8_t miso, int8_t clk, int8_t rst, int8_t cs, int8_t dcs, int8_t dreq, int8_t cardcs)
    : Adafruit_VS1053_FilePlayer(mosi, miso, clk, rst, cs, dcs, dreq, cardcs) {
}

//Fonctionne mais après un certain temps, et le BITRATE ne semble pas propre au fichier....
inline uint16_t FdS_Adafruit_VS1053_FilePlayer::getVS1053BitRate() {
  sciWrite(VS1053_REG_WRAMADDR, VS1053_PARAM_BITRATE);
  uint16_t bitrate = sciRead(VS1053_REG_WRAM) * 8;

  //Nécessaire??? à vérifier
  // Resync
  sciWrite(VS1053_REG_WRAMADDR, 0x1e29);
  sciWrite(VS1053_REG_WRAM, 0);

  return  bitrate;
}

inline void FdS_Adafruit_VS1053_FilePlayer::setPlaySpeed(uint16_t data) {
  sciWrite(VS1053_REG_WRAMADDR, VS1053_PARAM_PLAYSPEED);
  sciWrite(VS1053_REG_WRAM, data);
}

inline uint32_t FdS_Adafruit_VS1053_FilePlayer::getFilePosition() {
  if (currentTrack)
    return currentTrack.position();
  else
    return 0;
}

inline boolean FdS_Adafruit_VS1053_FilePlayer::jumpTo(uint32_t startPosition) {  

  if (!currentTrack) {
    return false;
  }
  
  currentTrack.seek(0);
  currentTrack.seek(startPosition);
  // Don't let the IRQ get triggered by accident here
  noInterrupts();

  // As explained in datasheet, set twice 0 in REG_DECODETIME to set time back to 0
  sciWrite(VS1053_REG_DECODETIME, 0x00);
  sciWrite(VS1053_REG_DECODETIME, 0x00);


  // Wait until it's ready for data
  while (!readyForData()) {
    // Handle other tasks or wait
  }

  // Fill the buffer
  while (playingMusic && readyForData()) {
    feedBuffer();
  }

  // OK going forward, we can use the IRQ
  interrupts();

  return true;
}
#endif
