#ifndef Range_H   // Vérifie si MACLASSE_H n'a pas été défini
#define Range_H   // Définit MACLASSE_H pour éviter les inclusions multiples

  class Range {
    public:
      uint8_t val;
      uint8_t min;
      uint8_t max;
      Range(uint8_t min, uint8_t max, uint8_t dft){
        this->val = dft;
        this->min = min;
        this->max = max;
      }
      void increase() {
        if(this->val < this->max) this->val++;
      }
      void decrease() {
        if(this->val > this->min) this->val--;
      }
  };
#endif