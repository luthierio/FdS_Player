class Debug {
private:
  Serial_* serialPtr = &Serial;
  bool enable;
  bool ramDebug;
public:
  
  Debug(Serial_* serialPtr = &Serial, bool enabled = true, bool ramDebug = true) : serialPtr(serialPtr), enable(enabled) , ramDebug(ramDebug){}

  void setEnabled(bool enabled) {
    this->enable = enabled;
  }
  void printRam() {
    serialPtr->println( "Free Ram :" + String(FreeRam(), DEC) + " bytes");
  }
  
  void print(const char* value) {
    if (enable) {
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }

  void print(const __FlashStringHelper* value) {
    if (enable) {
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }

  void print(const char* label, int value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(": "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }

  void print(const char* label, uint32_t value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(": "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }
  
  void print(const __FlashStringHelper* label, const char* value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(": "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }

  void print(const __FlashStringHelper* label, int value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(": "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }

  void print(const char* label, float value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(": "));
      serialPtr->println(value, 4);  // Display the float value with 4 decimals
      if (ramDebug) printRam();
    }
  }

  void print(const __FlashStringHelper* label, float value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(": "));
      serialPtr->println(value, 4);  // Display the float value with 4 decimals
      if (ramDebug) printRam();
    }
  }

  void print(const char* label, const char* value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(": "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }

  void print(const char* label, const __FlashStringHelper* value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(": "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }

  void print(const __FlashStringHelper* label, const __FlashStringHelper* value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(": "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }

  void print(const char* label, int id, int value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(" ("));
      serialPtr->print(id);
      serialPtr->print(F("): "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }

  void print(const char* label, int id, float value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(" ("));
      serialPtr->print(id);
      serialPtr->print(F("): "));
      serialPtr->println(value, 4);  // Display the float value with 4 decimals
      if (ramDebug) printRam();
    }
  }

  void print(const char* label, int id, const char* value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(" ("));
      serialPtr->print(id);
      serialPtr->print(F("): "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }
  void print(const char* label, const char* id, const char* value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(" ("));
      serialPtr->print(id);
      serialPtr->print(F("): "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }

  void print(const __FlashStringHelper* label, int id, int value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(" ("));
      serialPtr->print(id);
      serialPtr->print(F("): "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }

  void print(const __FlashStringHelper* label, int id, float value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(" ("));
      serialPtr->print(id);
      serialPtr->print(F("): "));
      serialPtr->println(value, 4);  // Display the float value with 4 decimals
      if (ramDebug) printRam();
    }
  }

  void print(const __FlashStringHelper* label, int id, const char* value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(" ("));
      serialPtr->print(id);
      serialPtr->print(F("): "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }

  void print(const __FlashStringHelper* label, int id, const __FlashStringHelper* value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(F(" ("));
      serialPtr->print(id);
      serialPtr->print(F("): "));
      serialPtr->println(value);
      if (ramDebug) printRam();
    }
  }
};
