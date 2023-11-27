
/**********************
* STATE:
***********************/

bool SHOULD_PLAY_NEXT = false;  

enum asfMode    { PLAYER,   PLAYLIST, BEAT, MENU, LOGO  };// Entier déguisé en string :-)
enum playMode   { ONEPLAY,  AUTO,   RANDOM,   REPEATONE };// Entier déguisé en string :-)
enum pitchMode  { OFF,      TEMPO,  PITCH };// Entier déguisé en string :-)

struct t_state{
  uint8_t MODE = PLAYER;
  uint8_t playMode = ONEPLAY;
  uint8_t dirNum = 0;
  uint8_t fileNum = 0;
  uint8_t playlistPosition[2] = {0,0}; //Placement du curseur dans les playlist pour autoplay
  uint8_t playlistMode = AUTO;
  uint8_t pitchStep = 5;
  uint8_t pitchRatio = 100;// En pourcentage, le ratio de pitch/tempo souhaité
  uint8_t pitchMode = OFF;
  boolean beatOn = false;
  uint8_t BPM = 100;
  uint8_t Beats = 2;
  uint8_t BeatsUp = 0;
};
t_state STATE;