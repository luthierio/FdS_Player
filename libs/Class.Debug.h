class Debug {
private:
  Serial_* serialPtr = &Serial;
  bool enable;
public:
  
  Debug(Serial_* serialPtr = &Serial, bool enabled = true) : serialPtr(serialPtr), enable(enabled) {}

  void setSerial(bool enabled) {
    this->enable = enabled;
  }
  
  void print(const char* value) {
    if (enable) {
      serialPtr->println(value);
    }
  }

  void print(const __FlashStringHelper* value) {
    if (enable) {
      serialPtr->println(value);
    }
  }

  void print(const char* label, int value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(": ");
      serialPtr->println(value);
    }
  }

  void print(const char* label, uint32_t value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(": ");
      serialPtr->println(value);
    }
  }

  void print(const __FlashStringHelper* label, int value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(": ");
      serialPtr->println(value);
    }
  }

  void print(const char* label, float value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(": ");
      serialPtr->println(value, 4);  // Display the float value with 4 decimals
    }
  }

  void print(const __FlashStringHelper* label, float value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(": ");
      serialPtr->println(value, 4);  // Display the float value with 4 decimals
    }
  }

  void print(const char* label, const char* value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(": ");
      serialPtr->println(value);
    }
  }

  void print(const char* label, const __FlashStringHelper* value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(": ");
      serialPtr->println(value);
    }
  }

  void print(const __FlashStringHelper* label, const __FlashStringHelper* value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(": ");
      serialPtr->println(value);
    }
  }

  void print(const char* label, int id, int value) {
    if (enable) {
      serialPtr->print(label);
      serialPtr->print(" (");
      serialPtr->print(id);
      serialPtr->print("): ");
      serialPtr->println(value);
    }
  }

  void print(const char* label, int id, float value) {
    if (enable) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value, 4);  // Display the float value with 4 decimals
    }
  }

  void print(const char* label, int id, const char* value) {
    if (enable) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value);
    }
  }
  void print(const char* label, const char* id, const char* value) {
    if (enable) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value);
    }
  }

  void print(const __FlashStringHelper* label, int id, int value) {
    if (enable) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value);
    }
  }

  void print(const __FlashStringHelper* label, int id, float value) {
    if (enable) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value, 4);  // Display the float value with 4 decimals
    }
  }

  void print(const __FlashStringHelper* label, int id, const char* value) {
    if (enable) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value);
    }
  }

  void print(const __FlashStringHelper* label, int id, const __FlashStringHelper* value) {
    if (enable) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value);
    }
  }
};
