/**********************
* DEBUG
***********************/
#define ASF_DEBUG_MODE 1
/**********************
* CONFIG CONST
***********************/
#define CREDITS     "V5.0-2023 S.Daron"
#define STARTSOUND  "/.ASF/Start.mp3"
#define ACCORDAGE   "/.ASF/Accordage.mp3"
#define BEATSOUND   "/.ASF/Beat.mp3"
#define BEATSOUND2  "/.ASF/Beat2.mp3"
#define PLAYLISTS_FILENAME  "Playlists.bin"
#define MARKERS_FILENAME    "Markers.bin"
#define STATE_FILENAME      "State.bin"

/**********************
* FEATHER WING MP3
***********************/
// Specifically for use with the Adafruit Feather, the pins are pre-set here!
// These are the pins used
#define VS1053_RESET   -1       // VS1053 reset pin (not used!)
#define VS1053_CS       6       // VS1053 chip select pin (output)
#define VS1053_DCS     10       // VS1053 Data/command select pin (output)
#define CARDCS          5       // Card chip select pin
#define VS1053_DREQ     9       // VS1053 Data request, ideally an Interrupt pin
#define SPI_SPEED SD_SCK_MHZ(4) // Required to int SD: SD.begin(CARDCS,SPI_SPEED)


