/**********************
* DEBUG
***********************/
#define ASF_DEBUG_MODE false
#define ASF_SLEEP_MODE false // Indique qu'il faut s'endormir de force
#define ASF_SPLASH_MODE false //Affiche le splash, sauvegarde en cours etc...
#define LOADED false
#define SERIAL_ON true

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
* SCREEN
***********************/
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

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

/**********************
* PITCH
***********************/
// AICTRL0 from table below. Voir https://www.vlsi.fi/fileadmin/software/VS10XX/pitchshifter.pdf
// AICTRL0 = +16384 × ratio/100. Voir https://www.vlsi.fi/fileadmin/software/VS10XX/pitchshifter.pdf
#define MIN_PITCH_STEP      0   
#define MAX_PITCH_STEP      10  
#define MIN_PITCH_RATIO        70  
#define MAX_PITCH_RATIO        134
#define MIN_PITCH_TEMPO_RATIO  50  
#define MAX_PITCH_TEMPO_RATIO  145 

/**********************
* INPUTS PINS
***********************/

// TRAD INPTS
#define VOLUME_PIN A1 
#define VOLUME 5           // Defaut volume

/**********************
* Multiplex
***********************/
#define PIN_ADDR_A 13
#define PIN_ADDR_B 12
#define PIN_ADDR_C 11
#define PIN_SIG    A0                           // Broche de signal

/**********************
* Interface
***********************/
const byte ROT_F_PIN[2] = {A3, A2};
const byte ROT_D_PIN[2] = {A5, A4};
const byte ROT_P_PIN[2] = {1 , 0 };

/**********************
* Modes
***********************/
enum asfMode    { PLAYER,   BEAT,   PLAYLIST,   ACTION  };// Entier déguisé en string :-)
enum playMode   { ONEPLAY,  AUTO,   RANDOM,   REPEATONE };// Entier déguisé en string :-)
enum pitchMode  { OFF,      TEMPO,  PITCH };// Entier déguisé en string :-)
enum pitchStyle { STEP,     RATIO };// Entier déguisé en string :-)
uint8_t ASF_MODE = PLAYER;

/**********************
* Custom
***********************/
#define SECONDS_PER_JUMP    4
#define SLEEP_INTERVAL      10000
#define SMALL_LOOP_INTERVAL 100
#define BIG_LOOP_INTERVAL   1000
#define BLINK_INTERVAL      500

#define DEBOUNCE_INTERVAL 500
#define LONG_PRESS_INTERVAL 1000
#define LONG_RELEASE_INTERVAL 2000
