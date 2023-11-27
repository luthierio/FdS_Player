#ifndef UTF8_CONVERTER_H
#define UTF8_CONVERTER_H

#include <Arduino.h>

class UTF8Converter {
public:
    UTF8Converter() {}

    char* convertToASCII(char* utf8String) {
        for (size_t i = 0; i < tableSize; ++i) {
            str_replace(utf8String, conversionTable[i][0], conversionTable[i][1]);
        }
        return utf8String;
    }

private:
    static const size_t tableSize = 40;

    // Déclaration des tableaux dans la mémoire flash
    static const char conversionTable[tableSize][2][4] PROGMEM;

    void str_replace(char* str, const char* find, const char* replace) {
        char* ptr = strstr(str, find);
        while (ptr != nullptr) {
            memmove(ptr + strlen(replace), ptr + strlen(find), strlen(ptr + strlen(find)) + 1);
            memcpy(ptr, replace, strlen(replace));
            ptr = strstr(ptr + strlen(replace), find);
        }
    }
};

// Initialisation des tableaux dans le fichier .cpp

// Déclaration et initialisation des tableaux dans la mémoire flash
const char UTF8Converter::conversionTable[tableSize][2][4] PROGMEM = {
    {"à", "a"}, {"á", "a"}, {"â", "a"}, {"ã", "a"},
    {"è", "e"}, {"é", "e"}, {"ê", "e"}, {"ë", "e"},
    {"ì", "i"}, {"í", "i"}, {"î", "i"}, {"ï", "i"},
    {"ò", "o"}, {"ó", "o"}, {"ô", "o"}, {"õ", "o"},
    {"ù", "u"}, {"ú", "u"}, {"û", "u"}, {"ü", "u"},
    {"À", "A"}, {"Á", "A"}, {"Â", "A"}, {"Ã", "A"},
    {"È", "E"}, {"É", "E"}, {"Ê", "E"}, {"Ë", "E"},
    {"Ì", "I"}, {"Í", "I"}, {"Î", "I"}, {"Ï", "I"},
    {"Ò", "O"}, {"Ó", "O"}, {"Ô", "O"}, {"Õ", "O"},
    {"Ù", "U"}, {"Ú", "U"}, {"Û", "U"}, {"Ü", "U"}
};

#endif  // UTF8_CONVERTER_H
