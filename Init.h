/**********************
* AUDIO CARD VS1053
***********************/
// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <SdFat.h>
SdFat SD;
#include <Adafruit_VS1053.h>

Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);