/**********************
* DEBUG
***********************/
#define ASF_DEBUG_MODE true

bool SERIAL_ON = ASF_DEBUG_MODE;
bool RAM_DEBUG_ON = false;
bool SERIAL_WAIT = false; //It true, wait serial to start

/**********************
* CONFIG CONST
***********************/
#define CREDITS             "V5.3-2024 S.Daron"
#define STARTSOUND          "/.ASF/Start.mp3"
#define ACCORDAGE           "/.ASF/Accordage.mp3"
#define BEATSOUND           "/.ASF/Beat.mp3"
#define BEATSOUND2          "/.ASF/Beat2.mp3"
#define PLAYLISTS_FILENAME  "/.Playlists.bin"
#define DATA_FILENAME       "/.Datas.bin"
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
#define MAX_FILENAME_LENGTH 150
#define MAX_DIRNAME_LENGTH 100
#define MAX_PATH_LENGTH 256

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

#define MIN_PITCH_STEP          0   
#define MAX_PITCH_STEP          10  
#define DFT_PITCH_STEP          5  
#define MIN_PITCH_RATIO         70  
#define MAX_PITCH_RATIO         134
#define MIN_PITCH_TEMPO_RATIO   50  
#define MAX_PITCH_TEMPO_RATIO   145 

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

#define MIN_VBAT          3.2    //3.5; // Voltage avec lequel la batterie est considérée vide https://learn.adafruit.com/adafruit-feather-m0-adalogger/power-management  
#define MAX_VBAT          4      // Voltage avec lequel la batterie est considérée pleine
#define VUSB_PLUGGED      4.2     //Voltage pour lequel le cable est considéré branché
/**********************
* Interface
***********************/
const byte ROT_F_PIN[2] = {A3, A2};
const byte ROT_D_PIN[2] = {A5, A4};
const byte ROT_P_PIN[2] = {1 , 0 };

/**********************
* Modes
***********************/
//enum pitchStyle { STEP,     RATIO };// Entier déguisé en string :-)

/**********************
* Audio
***********************/
#define MAX_VOLUME            0     // Un petit nombre signifie un volume fort
#define MIN_VOLUME            100   // Au dela de ce nombre 255 (Volume OFF) est envoyé.
#define DFT_BITRATE           128   //kbps, pas utilisé, mais si problème on se rabatera dessus
#define SECONDS_PER_JUMP      5

//SAMD_FEATHER_M0_EXPRESS
//These need a lot of RAM
//Not Fully tested...
#if defined(FEATHER_M4)

  #define NBR_MARKERS           20    //Nombre de marqueurs par fichier
  #define NBR_AUDIO_DATA        200   //Nombre de tableaux de marqueurs pour le boitier

  #define NBR_PLAYLISTS         8     //Nombre de playlists
  #define NBR_PLAYLIST_ITEMS    50    //Nombre de marqueurs par fichier

#else

  #define NBR_MARKERS           12    //Nombre de marqueurs par fichier
  #define NBR_AUDIO_DATA        100   //Nombre de tableaux de marqueurs pour le boitier

  #define NBR_PLAYLISTS         6     //Nombre de playlists
  #define NBR_PLAYLIST_ITEMS    50    //Nombre de marqueurs par fichier

#endif

/********************** 
* METRONOME
***********************/
#define MAX_BPM                 200   // BPM max possible
#define MIN_BPM                 30    // BPM min possible  
#define MAX_BEATS               12   // BPM max possible
#define MIN_BEATS               1    // BPM min possible  
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
#define DFT_CONFIRM         true 
enum Prompts { PL_ADD, PL_IMPORT, PL_EXPORT};
enum asfMode    { PLAYER,   PLAYLIST, METRONOME, PROMPT, LOGO  };// Entier déguisé en string :-)
enum playMode   { ONEPLAY,  AUTO,   RANDOM,   REPEATONE };// Entier déguisé en string :-)
//enum pitchMode  { OFF,      TEMPO,  PITCH };// Entier déguisé en string :-)
//enum CommandIDs { A_PROPOS, SAVE_ALL, MAR_SAVE, PL_SAVE, ST_SAVE, LOAD_ALL, MAR_LOAD, ST_LOAD, PL_LOAD, PL_IMPORT, PL_EXPOR, DEBUG_ON, ACCORD};

