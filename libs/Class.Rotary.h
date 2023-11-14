#ifndef Rotary_H
#define Rotary_H

class Rotary {
private:
  byte pin1;
  byte pin2;
  int position;
  int last_position;
  bool canLoop;
  byte state;
  byte direction;
  byte steps_per_click;
  int lower_bound;
  int upper_bound;
  int increment;
  enum DIRECTIONS { LEFT, RIGHT };

  typedef void (*CallbackFunction)(Rotary&);

  CallbackFunction change_cb;
  CallbackFunction right_cb;
  CallbackFunction left_cb;
  CallbackFunction upper_cb;
  CallbackFunction lower_cb;

  void resetPositionInternal(int p, bool fireCallback) {
    if (canLoop) {
      if (p > upper_bound) {
        last_position = lower_bound * steps_per_click;
      } else if (p < lower_bound) {
        last_position = upper_bound * steps_per_click;
      } else {
        last_position = p * steps_per_click;
      }
    } else {
      last_position = (lower_bound > p) ? lower_bound * steps_per_click : p * steps_per_click;
    }

    if (position != last_position) {
      position = last_position;
      if (fireCallback && change_cb != NULL)
        change_cb(*this);
    }
    direction = 0;
  }

  void updatePosition() {
    int s = state & 3;
    if (digitalRead(pin1))
      s |= 4;
    if (digitalRead(pin2))
      s |= 8;

    switch (s) {
    case 0:
    case 5:
    case 10:
    case 15:
      break;
    case 1:
    case 7:
    case 8:
    case 14:
      position += increment;
      break;
    case 2:
    case 4:
    case 11:
    case 13:
      position -= increment;
      break;
    case 3:
    case 12:
      position += 2 * increment;
      break;
    default:
      position -= 2 * increment;
      break;
    }
    state = (s >> 2);

    if (position != last_position && (abs(position - last_position) >= steps_per_click * increment)) {

      int current_position = getPosition();

      if (canLoop) {
        if (current_position > upper_bound) {
          current_position = lower_bound;
          position = lower_bound * steps_per_click;
        } else if (current_position < lower_bound) {
          current_position = upper_bound;
          position = upper_bound * steps_per_click;
        }
      }

      if (current_position >= lower_bound && current_position <= upper_bound) {

        if (position > last_position) {
          direction = RIGHT;
          if (right_cb != NULL)
            right_cb(*this);
        } else {
          direction = LEFT;
          if (left_cb != NULL)
            left_cb(*this);
        }
        last_position = position;
        if (change_cb != NULL)
          change_cb(*this);
      } else {
        position = last_position;
        if (current_position < lower_bound && lower_cb != NULL)
          lower_cb(*this);
        if (current_position > upper_bound && upper_cb != NULL)
          upper_cb(*this);
      }
    }
  }

public:
  Rotary() {}

  Rotary(byte pin1, byte pin2, bool canLoop = true, int lower_bound = INT16_MIN, int upper_bound = INT16_MAX, int initial_pos = 0, int increment = 1, byte steps_per_click = 4) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->canLoop = canLoop;
    setUpperBound(upper_bound);
    setLowerBound(lower_bound);
    setIncrement(increment);
    setStepsPerClick(steps_per_click);
    resetPositionInternal(initial_pos, false);
  }

  void begin() {
    pinMode(pin1, INPUT_PULLUP);
    pinMode(pin2, INPUT_PULLUP);
    loop();
  }

  void setCanLoop(byte canLoop) {
    this->canLoop = canLoop;
  }
  byte getCanLoop() {
    return this->canLoop;
  }
  void setUpperBound(int upper_bound) {
    this->upper_bound = (lower_bound < upper_bound) ? upper_bound : lower_bound;
  }

  void setLowerBound(int lower_bound) {
    this->lower_bound = (lower_bound < upper_bound) ? lower_bound : upper_bound;
  }

  int getUpperBound() {
    return this->upper_bound;
  }

  int getLowerBound() {
    return this->lower_bound;
  }

  void setChangedHandler(CallbackFunction f) {
    change_cb = f;
  }

  void setRightRotationHandler(CallbackFunction f) {
    right_cb = f;
  }

  void setLeftRotationHandler(CallbackFunction f) {
    left_cb = f;
  }

  void setUpperOverflowHandler(CallbackFunction f) {
    upper_cb = f;
  }

  void setLowerOverflowHandler(CallbackFunction f) {
    lower_cb = f;
  }

  void resetPosition(int p = 0, bool fireCallback = true) {
    resetPositionInternal(p, fireCallback);
  }

  void setIncrement(int inc) {
    increment = inc;
  }

  int getIncrement() {
    return increment;
  }

  void setStepsPerClick(int steps) {
    steps_per_click = (steps < 1) ? 1 : steps;
  }

  int getStepsPerClick() {
    return steps_per_click;
  }

  byte getDirection() {
    return direction;
  }

  String directionToString(byte direction) {
    return (direction == LEFT) ? "LEFT" : "RIGHT";
  }

  int getPosition() {
    return position / steps_per_click;
  }

  void update() {
    updatePosition();
  }
};
#endif
