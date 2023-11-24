/**********************
* DEBUG
***********************/
#define ASF_DEBUG_MODE false

bool SERIAL_ON = ASF_DEBUG_MODE;
bool SERIAL_WAIT = false; //It true, wait serial to start

/**********************
* CONFIG CONST
***********************/
#define CREDITS     "V5.0-2023 S.Daron"
#define STARTSOUND  "/.ASF/Start.mp3"
#define ACCORDAGE   "/.ASF/Accordage.mp3"
#define BEATSOUND   "/.ASF/Beat.mp3"
#define BEATSOUND2  "/.ASF/Beat2.mp3"
#define PLAYLISTS_FILENAME  "/.Playlists.bin"
#define MARKERS_FILENAME    "/.Markers.bin"
#define STATE_FILENAME      "/.State.bin"

/**********************
* SD
***********************/
#define BACKUP_REQUIRED false //If true create a backup before saving any file

/**********************
* FILES
***********************/
#define MIN_DIR_NUM 0 // OLED display width, in pixels
#define MAX_DIR_NUM 99 // OLED display width, in pixels
#define MIN_FILES_NUM 0 // OLED display width, in pixels
#define MAX_FILES_NUM 99 // OLED display width, in pixels

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

/**********************
* Multiplex
***********************/
#define PIN_ADDR_A        13
#define PIN_ADDR_B        12
#define PIN_ADDR_C        11
#define PIN_SIG           A0                           // Broche de signal
#define SEUIL_ANALOGIQUE  512          //Valeur sous laquelle on considère que c'est LOW en lecture analogique (requis avec des résistances de 100k)

#define MIN_VBAT              3.2    //3.5; // Voltage avec lequel la batterie est considérée vide https://learn.adafruit.com/adafruit-feather-m0-adalogger/power-management  
#define MAX_VBAT              4      // Voltage avec lequel la batterie est considérée pleine
/**********************
* Interface
***********************/
const byte ROT_F_PIN[2] = {A3, A2};
const byte ROT_D_PIN[2] = {A5, A4};
const byte ROT_P_PIN[2] = {1 , 0 };

/**********************
* Modes
***********************/
enum CommandIDs { A_PROPOS, SAVE_ALL, MAR_SAVE, PL_SAVE, ST_SAVE, LOAD_ALL, MAR_LOAD, ST_LOAD, PL_LOAD, PL_EXPOR, DEBUG_ON, ACCORD};
//enum pitchStyle { STEP,     RATIO };// Entier déguisé en string :-)

/**********************
* Audio
***********************/
#define BITRATE               64000  //Ce serait mieux de le prendre du fichier mais pour le moment c'est le plus simple
#define SECONDS_PER_JUMP      2

#define NBR_MARKERS           10    //Nombre de marqueurs par 
#define NBR_MARKER_ARRAYS     30    //Nombre de tableaux de marqueurs pour le boitier

#define MAX_VOLUME            0      // Un petit nombre signifie un volume fort
#define MIN_VOLUME            100    // Au dela de ce nombre 255 (Volume OFF) est envoyé.

#define NBR_PLAYLISTS        8    //Nombre de tableaux de marqueurs pour le boitier
#define NBR_PLAYLIST_ITEMS  20    //Nombre de marqueurs par fichier

/**********************
* UX
***********************/
#define SLEEP_INTERVAL      10000
#define SMALL_LOOP_INTERVAL 100
#define BIG_LOOP_INTERVAL   2000
#define BLINK_INTERVAL      500
#define MSG_DELAY           100
#define ERROR_MSG_DELAY     2000

#define DEBOUNCE_INTERVAL 200
#define LONG_PRESS_INTERVAL 500
#define LONG_RELEASE_INTERVAL 2000

/**********************
* DISPLAY
***********************/

