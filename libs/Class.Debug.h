class Debug {
public:
  Debug() {
    // Constructor if needed
  }

  static void print(const char* value) {
    if (SERIAL_ON) {
      Serial.println(value);
    }
  }

  static void print(const __FlashStringHelper* value) {
    if (SERIAL_ON) {
      Serial.println(value);
    }
  }

  static void print(const char* label, int value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(": ");
      Serial.println(value);
    }
  }

  static void print(const __FlashStringHelper* label, int value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(": ");
      Serial.println(value);
    }
  }

  static void print(const char* label, float value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(": ");
      Serial.println(value, 4);  // Display the float value with 4 decimals
    }
  }

  static void print(const __FlashStringHelper* label, float value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(": ");
      Serial.println(value, 4);  // Display the float value with 4 decimals
    }
  }

  static void print(const char* label, const char* value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(": ");
      Serial.println(value);
    }
  }

  static void print(const __FlashStringHelper* label, const __FlashStringHelper* value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(": ");
      Serial.println(value);
    }
  }

  static void print(const char* label, int id, int value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value);
    }
  }

  static void print(const char* label, int id, float value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value, 4);  // Display the float value with 4 decimals
    }
  }

  static void print(const char* label, int id, const char* value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value);
    }
  }

  static void print(const __FlashStringHelper* label, int id, int value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value);
    }
  }

  static void print(const __FlashStringHelper* label, int id, float value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value, 4);  // Display the float value with 4 decimals
    }
  }

  static void print(const __FlashStringHelper* label, int id, const char* value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value);
    }
  }

  static void print(const __FlashStringHelper* label, int id, const __FlashStringHelper* value) {
    if (SERIAL_ON) {
      Serial.print(label);
      Serial.print(" (");
      Serial.print(id);
      Serial.print("): ");
      Serial.println(value);
    }
  }
};
