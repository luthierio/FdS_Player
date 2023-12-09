#include <Adafruit_VS1053.h>

class Metronome {
private:
  Adafruit_VS1053_FilePlayer *player;
  int bpm = 100;            // Battements par minute
  int beatsPerBar = 4;    // Nombre de battements par mesure
  unsigned long lastMillis;
  int beatCount;
  const char *highBeatFile;
  const char *lowBeatFile;

public:
  Metronome(Adafruit_VS1053_FilePlayer *player, const char *highBeatFile, const char *lowBeatFile) {
    this->player = player;
    this->bpm = 120;  // Valeur par défaut pour le BPM
    this->beatsPerBar = 4;  // Valeur par défaut pour le nombre de battements par mesure
    this->lastMillis = 0;
    this->beatCount = 0;
    this->highBeatFile = highBeatFile;
    this->lowBeatFile = lowBeatFile;
  }

  void begin() {
    if (!player->begin()) {
      Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
      while (1);
    }
    player->softReset();
    player->setVolume(20, 20);
  }

  void setBpm(int bpm) {
    this->bpm = bpm;
  }
  int getBpm() {
    return this->bpm;
  }
  
  void setBeatsPerBar(int beatsPerBar) {
    this->beatsPerBar = beatsPerBar;
  }
  int getBeatsPerBar() {
    return this->beatsPerBar;
  }

  int getBeat() {
    return this->beatCount;
  }


  void playClick(const char *filename) {
    player->startPlayingFile(filename);
    while (player->playingMusic) {
      // Wait for playback to complete
    }
  }

  void update() {
    unsigned long now = millis();
    unsigned long timePerBeat = 60000 / bpm; // Milliseconds per beat

    if (now - lastMillis >= timePerBeat) {
      lastMillis = now;
      beatCount++;

      if (beatCount > beatsPerBar) {
        beatCount = 1; // Reset the beat count at the beginning of each bar
      }

      if (beatCount == 1) {
        playClick(highBeatFile); // Play a different sound for the first beat of the bar
      } else {
        playClick(lowBeatFile); // Play a different sound for non-first beats
      }
    }
  }
};
