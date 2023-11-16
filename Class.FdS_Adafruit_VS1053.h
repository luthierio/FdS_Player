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

  uint16_t getBitRate();
  void setPlaySpeed(uint16_t data);
  uint32_t getFilePosition();
  boolean startPlayingAtPosition(const char *trackname, uint32_t startPosition);
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
inline uint16_t FdS_Adafruit_VS1053_FilePlayer::getBitRate() {
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

inline boolean FdS_Adafruit_VS1053_FilePlayer::startPlayingAtPosition(const char *trackname, uint32_t startPosition) {  

  // Reset playback
  sciWrite(VS1053_REG_MODE, VS1053_MODE_SM_LINE1 | VS1053_MODE_SM_SDINEW | VS1053_MODE_SM_LAYER12);
  // Resync
  sciWrite(VS1053_REG_WRAMADDR, 0x1e29);
  sciWrite(VS1053_REG_WRAM, 0);

  currentTrack = SD.open(trackname);
  if (!currentTrack) {
    return false;
  }
  
  // We know we have a valid file. Check if .mp3
  // If so, check for ID3 tag and jump it if present.
  if (isMP3File(trackname)) {
    //currentTrack.seek(mp3_ID3Jumper(currentTrack));
    if (startPosition) {
      // Seek to the specified position
      currentTrack.seek(startPosition);
    }  
  }
  // Don't let the IRQ get triggered by accident here
  noInterrupts();

  // As explained in datasheet, set twice 0 in REG_DECODETIME to set time back to 0
  sciWrite(VS1053_REG_DECODETIME, 0x00);
  sciWrite(VS1053_REG_DECODETIME, 0x00);

  playingMusic = true;

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