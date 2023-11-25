// FdS_Adafruit_VS1053.h
#ifndef FDS_ADAFRUIT_VS1053_H
#define FDS_ADAFRUIT_VS1053_H

#include <Adafruit_VS1053.h>
#define VS1053_PARAM_PLAYSPEED 0x1E04
#define VS1053_PARAM_BITRATE 0x1E05


//avr pgmspace library for storing the LUT in program flash instead of sram
#include <avr/pgmspace.h>

/**
 * \brief bitrate lookup table
 *
 * This is a table to decode the bitrate as per the MP3 file format,
 * as read by the SdCard
 *
 * <A HREF = "http://www.mp3-tech.org/programmer/frame_header.html" > www.mp3-tech.org </A>
 * \note PROGMEM macro forces to Flash space.
 * \warning This consums 190 bytes of flash
 */
static const uint16_t bitrate_table[15][6] PROGMEM = {
                 { 0,   0,  0,  0,  0,  0}, //0000
                 { 32, 32, 32, 32,  8,  8}, //0001
                 { 64, 48, 40, 48, 16, 16}, //0010
                 { 96, 56, 48, 56, 24, 24}, //0011
                 {128, 64, 56, 64, 32, 32}, //0100
                 {160, 80, 64, 80, 40, 40}, //0101
                 {192, 96, 80, 96, 48, 48}, //0110
                 {224,112, 96,112, 56, 56}, //0111
                 {256,128,112,128, 64, 64}, //1000
                 {288,160,128,144, 80, 80}, //1001
                 {320,192,160,160, 96, 69}, //1010
                 {352,224,192,176,112,112}, //1011
                 {384,256,224,192,128,128}, //1100
                 {416,320,256,224,144,144}, //1101
                 {448,384,320,256,160,160}  //1110
               };


class FdS_Adafruit_VS1053_FilePlayer : public Adafruit_VS1053_FilePlayer {
public:
  FdS_Adafruit_VS1053_FilePlayer(int8_t rst, int8_t cs, int8_t dcs, int8_t dreq, int8_t cardcs);
  FdS_Adafruit_VS1053_FilePlayer(int8_t cs, int8_t dcs, int8_t dreq, int8_t cardcs);
  FdS_Adafruit_VS1053_FilePlayer(int8_t mosi, int8_t miso, int8_t clk, int8_t rst, int8_t cs, int8_t dcs, int8_t dreq, int8_t cardcs);

  uint16_t getVS1053BitRate();
  void getMP3BitRate();
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

void FdS_Adafruit_VS1053_FilePlayer::getMP3BitRate() {
//char* fileName
  //look for first MP3 frame (11 1's)
/*
  bitrate = 0;
  uint8_t temp = 0;
  uint8_t row_num =0;
    for(uint16_t i = 0; i<65535; i++) {
      if(track.read() == 0xFF) {

        temp = track.read();

        if(((temp & 0b11100000) == 0b11100000) && ((temp & 0b00000110) != 0b00000000)) {

          //found the 11 1's
          //parse version, layer and bitrate out and save bitrate
          if(!(temp & 0b00001000)) { //!true if Version 1, !false version 2 and 2.5
            row_num = 3;
          }
          else if((temp & 0b00000110) == 0b00000100) { //true if layer 2, false if layer 1 or 3
            row_num += 1;
          }
          else if((temp & 0b00000110) == 0b00000010) { //true if layer 3, false if layer 2 or 1
            row_num += 2;
          } else {
            continue; // Not found, need to skip the rest and continue looking.
                      // \warning But this can lead to a dead end and file end of file.
          }

          //parse bitrate code from next byte
          temp = track.read();
          temp = temp>>4;

          //lookup bitrate
          bitrate = pgm_read_word_near ( &(bitrate_table[temp][row_num]) );

          //convert kbps to Bytes per mS
          bitrate /= 8;

          //record file position
          track.seekCur(-3);
          start_of_music = track.curPosition();

//          Serial.print(F("POS: "));
//          Serial.println(start_of_music);

//          Serial.print(F("Bitrate: "));
//          Serial.println(bitrate);

          //break out of for loop
          break;

        }
      }
    }
    */
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
