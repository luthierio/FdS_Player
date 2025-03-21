
Debug DEBUG_(&Serial, SERIAL_ON, RAM_DEBUG_ON);
byte INTERRUPTS = true; // IF false, buttons etc desactivated
/**********************
* FAT Files
***********************/
SdFat SD;

/**********************
* AUDIO CARD VS1053
***********************/

FdS_Adafruit_VS1053_FilePlayer AUDIO =
  FdS_Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);
Pitcher PITCHER = Pitcher(&AUDIO);

FilePicker FILE_(&SD);
FileManager SD_FS(&SD);

MP3File MP3;
bool MP3_MUST_LOAD = false; //Boolean pour charger les MP3 via les loops

Metronome METRONOME_(&AUDIO, BEATSOUND, BEATSOUND2); // BPM = 120, 4 beats per bar, with specific beat files

uint8_t VOLUME = 10;          // Defaut volume

/**********************
* DATAS & PLAYLISTS
***********************/
//PlaylistItem PLAYLISTS[NBR_PLAYLISTS][NBR_PLAYLIST_ITEMS];
Playlist PLAYLISTS[NBR_PLAYLISTS];
PlaylistManager PLAYLISTS_(PLAYLISTS,NBR_PLAYLISTS);

audioData DATAS[NBR_AUDIO_DATA];
audioDataManager DATA_MANAGER(&FILE_, DATAS, NBR_AUDIO_DATA);

/**********************
* SCREEN
***********************/
Adafruit_SSD1306 SCREEN_(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/**********************
* Multiplex
***********************/

int BTN_CHANNEL[] = {2, 3, 4, 5, 6, 7};
Multiplex MUX(PIN_ADDR_A, PIN_ADDR_B, PIN_ADDR_C, PIN_SIG, SEUIL_ANALOGIQUE);
ButtonHandler BUTTONS(6, DEBOUNCE_INTERVAL, LONG_PRESS_INTERVAL, LONG_RELEASE_INTERVAL);

/**********************
* Rotary Encoders
***********************/
Rotary ROTARIES[3] = {
  Rotary( ROT_F_PIN[0], ROT_F_PIN[1], true , MIN_FILES_NUM, MAX_FILES_NUM),
  Rotary( ROT_D_PIN[0], ROT_D_PIN[1], true , MIN_DIR_NUM, MAX_DIR_NUM),
  Rotary( ROT_P_PIN[0], ROT_P_PIN[1], false ,MIN_PITCH_STEP, MAX_PITCH_STEP, DFT_PITCH_STEP ),
};
Rotary* R_FILES = &ROTARIES[0];
Rotary* R_DIR   = &ROTARIES[1];
Rotary* R_PITCH = &ROTARIES[2];

/**********************
* WakeUp and Sleep
***********************/

SleepWatch SLEEP_WATCH(SLEEP_INTERVAL);


/**********************
* Energy
***********************/
float VUSB;           // Tension mesurée pour USB (si >
float VBat;


/**********************
* PROMPT_IDS:
***********************/

uint8_t PROMPT_ID;
uint8_t CONTEXT;
bool CONFIRM = DFT_CONFIRM;

/**********************
* DISPLAY:
***********************/
#define SILENT true
DisplayController DISPLAY_(&SCREEN_,&AUDIO, &FILE_, &PITCHER, &PLAYLISTS_, &STATE, &DATA_MANAGER, &MP3, &METRONOME_);


