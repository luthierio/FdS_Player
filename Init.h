

/**********************
* SCREEN
***********************/
Adafruit_SSD1306 SCREEN_(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Display DISPLAY_(SCREEN_);
/**********************
* FAT Files
***********************/
SdFat SD;

/**********************
* AUDIO CARD VS1053
***********************/

Adafruit_VS1053_FilePlayer AUDIO =
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);
Pitcher PITCHER = Pitcher(&AUDIO);
FilePicker FILE_(&SD);

/**********************
* Multiplex
***********************/

int BTN_CHANNEL[] = {2, 3, 4, 5, 6, 7};
Multiplex MUX(PIN_ADDR_A, PIN_ADDR_B, PIN_ADDR_C, PIN_SIG);
ButtonHandler BUTTONS(6);


/**********************
* Rotary Encoders
***********************/
Rotary ROTARIES[3] = {
  Rotary( ROT_F_PIN[0], ROT_F_PIN[1], true , 0, 99),
  Rotary( ROT_D_PIN[0], ROT_D_PIN[1], true , 0, 99),
  Rotary( ROT_P_PIN[0], ROT_P_PIN[1], false ,0, 9, 5 ),
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
* Interface
***********************/

char  activeSoundPath[512];

/**********************
* State
***********************/
//Toutes les variables à sauvegarder sur la carte SD

struct t_state{
  uint8_t dirNum = 0;
  uint8_t fileNum = 0;
  uint8_t pitchStep = 5;
  uint8_t pitchRatio = 100;// En pourcentage, le ratio de pitch/tempo souhaité
  boolean beatOn = false;
  uint8_t BPM = 100;
  uint8_t Beats = 2;
  uint8_t BeatsUp = 0;
  uint8_t playMode = ONEPLAY;
  uint8_t pitchMode = OFF;
  uint8_t pitchStyle = STEP;
  uint8_t playlistID = 0;
  uint8_t playlistReferenceID = 0;
  uint8_t playingPosition[2] = {0,0}; //Placement du curseur dans les playlist pour autoplay
  uint8_t playlistMode = ONEPLAY;
};
t_state STATE;
