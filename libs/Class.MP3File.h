#ifndef MP3File_H
#define MP3File_H

#include <SdFat.h>

#define TRACK_TITLE 3
#define TRACK_ARTIST 33
#define TRACK_ALBUM 63
#define TRACK_YEAR 93
#define TRACK_COMMENT 97
#define TRACK_GENRE 127
#define MAX_STRING_LENGTH 31
#define FILE_EXTENSION_LENGTH 4

struct ID3v1Info {
    char title[MAX_STRING_LENGTH + 1];
    char artist[MAX_STRING_LENGTH + 1];
    char album[MAX_STRING_LENGTH + 1];
    char year[5]; // Assuming the year is a 4-digit string
    char comment[29]; // 28 bytes for comment plus a null terminator
    uint8_t genre; // Genre index
};

class MP3File : public File {
public:
    uint16_t bitrate; // kbps
    uint8_t format;    //{ "V1L1", "V1L2", "V1L3", "V2L1", "V2L2", "V2L3"}
    int start_of_music;
    bool isMP3;
    bool hasID3V1;

    ID3v1Info ID3V1;

    MP3File() {
        // Constructor - You can initialize variables or allocate resources here.
    }

    void open(const char *fileName) {
        isMP3 = isMP3File(fileName);
        File::open(fileName);

        if (isMP3) {
            readFrameHeader();
            hasID3V1 = checkID3V1();
        }
        if (hasID3V1) {
            getID3V1(ID3V1);
        }
    }

    bool checkID3V1() {
        // Check if the last 128 bytes contain "TAG"
        seekEnd(-128);
        char tag[4];
        read(tag, 4);
        return strncmp(tag, "TAG", 3) == 0;
    }

    void getID3V1(ID3v1Info &info) {
        // skip to end
        seekEnd(-128 + TRACK_TITLE);
        // read 30 bytes of tag information at -128 + offset
        read(info.title, 30);
        info.title[30] = '\0';

        seekEnd(-128 + TRACK_ARTIST);
        read(info.artist, 30);
        info.artist[30] = '\0';

        seekEnd(-128 + TRACK_ALBUM);
        read(info.album, 30);
        info.album[30] = '\0';

        seekEnd(-128 + TRACK_YEAR);
        read(info.year, 4);
        info.year[4] = '\0';

        seekEnd(-128 + TRACK_COMMENT);
        read(info.comment, 28);
        info.comment[28] = '\0';

        seekEnd(-128 + TRACK_GENRE);
        info.genre = read();

    }

    bool isMP3File(const char *fileName) {
        return (strlen(fileName) > FILE_EXTENSION_LENGTH) &&
               !strcasecmp(fileName + strlen(fileName) - FILE_EXTENSION_LENGTH, ".mp3");
    }

    uint32_t getBytePerSecond() {
        return bitrate*1000 / 8; //kbps -> byte per second
    }

    uint16_t readFrameHeader() {
        // look for the first MP3 frame (11 1's)
        bitrate = 0;
        format = 0;
        uint8_t temp = 0;
        for (uint16_t i = 0; i < 65535; i++) {
            if (read() == 0xFF) {
                temp = read();
                if (((temp & 0b11100000) == 0b11100000) && ((temp & 0b00000110) != 0b00000000)) {
                    // found the 11 1's
                    // parse version, layer, and bitrate out and save bitrate
                    if (!(temp & 0b00001000)) { //!true if Version 1, !false version 2 and 2.5
                        format = 3;
                    } else if ((temp & 0b00000110) == 0b00000100) { // true if layer 2, false if layer 1 or 3
                        format += 1;
                    } else if ((temp & 0b00000110) == 0b00000010) { // true if layer 3, false if layer 2 or 1
                        format += 2;
                    } else {
                        continue; // Not found, need to skip the rest and continue looking.
                        // \warning But this can lead to a dead end and file end of file.
                    }

                    // parse bitrate code from the next byte
                    temp = read();
                    temp = temp >> 4;

                    // lookup bitrate
                    bitrate = getBitrateFromTable(temp, format);
                    
                    seekCur(-3);
                    start_of_music = curPosition();

                    // break out of the for loop
                    break;
                }
            }
        }
        return bitrate;
    }

private:
    static const uint16_t bitrate_table[15][6];

    uint16_t getBitrateFromTable(uint8_t index, uint8_t format) {
        return pgm_read_word_near(&(bitrate_table[index][format]));
    }
};

const uint16_t MP3File::bitrate_table[15][6] = {
    {0, 0, 0, 0, 0, 0},      // 0000
    {32, 32, 32, 32, 8, 8},   // 0001
    {64, 48, 40, 48, 16, 16}, // 0010
    {96, 56, 48, 56, 24, 24}, // 0011
    {128, 64, 56, 64, 32, 32}, // 0100
    {160, 80, 64, 80, 40, 40}, // 0101
    {192, 96, 80, 96, 48, 48}, // 0110
    {224, 112, 96, 112, 56, 56}, // 0111
    {256, 128, 112, 128, 64, 64}, // 1000
    {288, 160, 128, 144, 80, 80}, // 1001
    {320, 192, 160, 160, 96, 69}, // 1010
    {352, 224, 192, 176, 112, 112}, // 1011
    {384, 256, 224, 192, 128, 128}, // 1100
    {416, 320, 256, 224, 144, 144}, // 1101
    {448, 384, 320, 256, 160, 160}  // 1110
};

#endif
