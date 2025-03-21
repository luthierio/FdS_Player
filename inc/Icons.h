/*
Pour générer des images:
http://javl.github.io/image2cpp/

*/

const unsigned char logo[] PROGMEM = {
  0x0a, 0x08, 0x0a, 0xff,   /*Color of index 0*/
  0xcd, 0xce, 0xce, 0xff,   /*Color of index 1*/
  0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x7d, 0xbe, 0x00, 0x00, 0x00,   0x00, 0x00, 0x03, 0xfd, 0xbf, 0xc0, 0x00, 0x00,   0x00, 0x00, 0x1f, 0xfc, 0x3f, 0xf8, 0x00, 0x00,   0x00, 0x00, 0x3f, 0x8f, 0xf1, 0xfc, 0x00, 0x00,   0x00, 0x00, 0xfc, 0x0f, 0xf0, 0x3f, 0x00, 0x00,   0x00, 0x03, 0xf0, 0x00, 0x00, 0x0f, 0xc0, 0x00,   0x00, 0x07, 0xc0, 0x00, 0x00, 0x03, 0xe0, 0x00,   0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00,   0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00,   0x00, 0x3c, 0x00, 0x21, 0x84, 0x00, 0x3c, 0x00,   0x00, 0x78, 0x00, 0x31, 0x8c, 0x00, 0x1e, 0x00,   0x00, 0xf0, 0x00, 0x31, 0x8c, 0x00, 0x0f, 0x00,   0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,   0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80,   0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80,   0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,   0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,   0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,   0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,   0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70,   0x0e, 0x03, 0xff, 0xc0, 0x0e, 0x3e, 0x80, 0x70,   0x0e, 0x00, 0xe0, 0xe0, 0x1e, 0x67, 0x80, 0x70,   0x1c, 0x00, 0xe0, 0x60, 0x0e, 0xc3, 0x80, 0x38,   0x1c, 0x00, 0xe0, 0x20, 0x06, 0xc1, 0x80, 0x38,   0x1c, 0x00, 0xe0, 0x00, 0x06, 0xc0, 0x80, 0x38,   0xff, 0x00, 0xe0, 0x80, 0x06, 0xc0, 0x00, 0xff,   0xff, 0x00, 0xe0, 0x80, 0x06, 0xf0, 0x00, 0xff,   0xc3, 0x00, 0xff, 0x81, 0xfe, 0x7e, 0x00, 0xc3,   0xdb, 0x00, 0xff, 0x83, 0x0e, 0x1f, 0x80, 0xdb,   0xdb, 0x00, 0xe0, 0x86, 0x06, 0x03, 0xc0, 0xdb,   0xc3, 0x00, 0xe0, 0x84, 0x06, 0x00, 0xc0, 0xc3,   0xff, 0x00, 0xe0, 0x0c, 0x06, 0x80, 0xe0, 0xff,   0xff, 0x00, 0xe0, 0x0c, 0x06, 0x80, 0x60, 0xff,   0x1c, 0x00, 0xe0, 0x0c, 0x06, 0xc0, 0x60, 0x38,   0x1c, 0x00, 0xe0, 0x06, 0x06, 0xc0, 0xc0, 0x38,   0x1c, 0x00, 0xe0, 0x07, 0x0f, 0xe0, 0xc0, 0x38,   0x0e, 0x00, 0xf0, 0x03, 0xff, 0x7f, 0x80, 0x70,   0x0e, 0x03, 0xfc, 0x01, 0xf4, 0x1f, 0x00, 0x70,   0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70,   0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,   0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,   0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,   0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,   0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80,   0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80,   0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,   0x00, 0xf0, 0x00, 0x31, 0x8c, 0x00, 0x0f, 0x00,   0x00, 0x78, 0x00, 0x31, 0x8c, 0x00, 0x1e, 0x00,   0x00, 0x3c, 0x00, 0x21, 0x84, 0x00, 0x3c, 0x00,   0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00,   0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00,   0x00, 0x07, 0xc0, 0x00, 0x00, 0x03, 0xe0, 0x00,   0x00, 0x03, 0xf0, 0x00, 0x00, 0x0f, 0xc0, 0x00,   0x00, 0x00, 0xfc, 0x0f, 0xf0, 0x3f, 0x00, 0x00,   0x00, 0x00, 0x3f, 0x8f, 0xf1, 0xfc, 0x00, 0x00,   0x00, 0x00, 0x1f, 0xfc, 0x3f, 0xf8, 0x00, 0x00,   0x00, 0x00, 0x03, 0xfd, 0xbf, 0xc0, 0x00, 0x00,   0x00, 0x00, 0x00, 0x7d, 0xbe, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00,
};


const unsigned char LOGO_128x64 [] PROGMEM ={
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x0f, 0xfc, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x3f, 0xf0, 
	0x0f, 0xfc, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x3f, 0xf0, 
	0x0c, 0x0c, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x30, 0x30, 
	0x0c, 0x0c, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x30, 0x30, 
	0x0c, 0xcf, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x61, 0x86, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xf3, 0x30, 
	0x0c, 0xcf, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x61, 0x86, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf3, 0x30, 
	0x0c, 0x0c, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x30, 0x30, 
	0x0c, 0x0c, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x30, 0x30, 
	0x0f, 0xfc, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x3f, 0xf0, 
	0x0f, 0xfc, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x3f, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xa4, 0x42, 0x08, 0x10, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x30, 0x00, 0x04, 0x00, 0x00, 0x47, 0xe0, 0x0c, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x30, 0x00, 0x0e, 0x00, 0xfe, 0x7f, 0xf0, 0x0c, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x30, 0x00, 0x0e, 0x01, 0x0c, 0x18, 0x10, 0x0c, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x30, 0x00, 0x16, 0x01, 0x04, 0x18, 0x10, 0x0c, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x30, 0x00, 0x33, 0x03, 0x00, 0x18, 0x00, 0x0c, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x30, 0x00, 0x23, 0x01, 0x80, 0x18, 0x60, 0x0c, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x20, 0x00, 0x61, 0x81, 0xe0, 0x1f, 0xe0, 0x04, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x20, 0x00, 0x41, 0x80, 0xfc, 0x1f, 0xe0, 0x04, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x20, 0x00, 0xff, 0xc0, 0x1e, 0x18, 0x60, 0x04, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x20, 0x00, 0x80, 0xc0, 0x07, 0x18, 0x00, 0x04, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x30, 0x01, 0x80, 0xc1, 0x03, 0x18, 0x00, 0x0c, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x30, 0x01, 0x80, 0x61, 0x01, 0x18, 0x00, 0x0c, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x30, 0x01, 0x00, 0x61, 0x03, 0x18, 0x00, 0x0c, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x30, 0x03, 0x00, 0x73, 0x83, 0x18, 0x00, 0x0c, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x30, 0x07, 0x00, 0x79, 0xce, 0x38, 0x00, 0x0c, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x30, 0x0f, 0x80, 0xf8, 0x78, 0x7f, 0x00, 0x0c, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x10, 0x42, 0x25, 
	0xa4, 0x42, 0x08, 0x10, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x10, 0x42, 0x25, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x0f, 0xfc, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x7f, 0xe0, 
	0x0f, 0xfc, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x7f, 0xe0, 
	0x0c, 0x0c, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x60, 0x60, 
	0x0c, 0x0c, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x60, 0x60, 
	0x0c, 0xcf, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x61, 0x86, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xe6, 0x60, 
	0x0c, 0xcf, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x61, 0x86, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xe6, 0x60, 
	0x0c, 0x0c, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x60, 0x60, 
	0x0c, 0x0c, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x60, 0x60, 
	0x0f, 0xfc, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x7f, 0xe0, 
	0x0f, 0xfc, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x7f, 0xe0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char folderIcon16[] PROGMEM = 
{       
  0b00000000, 0b00000000, //        
  0b11111111, 0b00000000, // ########
  0b11111111, 0b10000000, // #########
  0b11111111, 0b11111111, // ################
  0b11111111, 0b11111111, // ################
  0b11000000, 0b00000011, // ##            ##
  0b11000000, 0b00000011, // ##            ##
  0b11000000, 0b00000011, // ##            ##
  0b11000000, 0b00000011, // ##            ##
  0b11000000, 0b00000011, // ##            ##
  0b11000000, 0b00000011, // ##            ##
  0b11000000, 0b00000011, // ##            ##
  0b11000000, 0b00000011, // ##            ##
  0b11111111, 0b11111111, // ################
  0b11111111, 0b11111111, // ################
  0b00000000, 0b00000000, //     
};
const unsigned char sdIcon16[] PROGMEM = 
{           
  0b00000000, 0b00000000, //             
  0b00011111, 0b11111110, //             
  0b00101101, 0b10110010, //             
  0b01001101, 0b10110010, //             
  0b01001101, 0b10110010, //             
  0b01001101, 0b10110010, //             
  0b01000000, 0b00000010, //             
  0b01000000, 0b00000010, //             
  0b01000111, 0b01100010, //             
  0b01000100, 0b01010010, //             
  0b01000111, 0b01010010, //             
  0b01000001, 0b01010010, //             
  0b01000111, 0b01100010, //            
  0b01000000, 0b00000010, //              
  0b01111111, 0b11111110, //            
  0b00000000, 0b00000000, // 
};
const unsigned char arrowRight16[] PROGMEM = 
{           
  0b00000000, 0b00000000, //  
  0b00000000, 0b00000000, //  
  0b00000000, 0b00000000, // 
  0b00000000, 0b00000000, //              
  0b00000000, 0b11000000, //             
  0b00000000, 0b11110000, //              
  0b01111111, 0b11111100, //            
  0b11111111, 0b11111111, //             
  0b11111111, 0b11111111, //             
  0b01111111, 0b11111100, //             
  0b00000000, 0b11110000, //             
  0b00000000, 0b11000000, //             
  0b00000000, 0b00000000, //            
  0b00000000, 0b00000000, //              
  0b00000000, 0b00000000, //            
  0b00000000, 0b00000000, // 
};
const unsigned char arrowLeft16[] PROGMEM = 
{           
  0b00000000, 0b00000000, //  
  0b00000000, 0b00000000, //  
  0b00000000, 0b00000000, // 
  0b00000000, 0b00000000, //              
  0b00000011, 0b00000000, //             
  0b00001111, 0b00000000, //              
  0b00111111, 0b11111110, //            
  0b11111111, 0b11111111, //             
  0b11111111, 0b11111111, //             
  0b00111111, 0b11111110, //             
  0b00001111, 0b00000000, //             
  0b00000011, 0b00000000, //             
  0b00000000, 0b00000000, //            
  0b00000000, 0b00000000, //              
  0b00000000, 0b00000000, //            
  0b00000000, 0b00000000, // 
};
const unsigned char folderIcon8[] PROGMEM = 
{               
  0b00000000,   
  0b11110000,   
  0b11111000,   
  0b11111111,  
  0b11111111,  
  0b11111111,  
  0b11111111,   
  0b00000000,       
};
const unsigned char playModeRandomIcon[] PROGMEM = 
{                
  0b10000000, 0b01111111,  
  0b11000001, 0b11111110,  
  0b01100011, 0b00011100,
  0b00110110, 0b10011000,
  0b00001100, 0b00000000,
  0b00011000, 0b00000000,
  0b00110110, 0b00011000,
  0b01100011, 0b00011100,
  0b11000001, 0b11111110, 
  0b10000000, 0b11111111,     
};
const unsigned char playModeContinIcon[] PROGMEM = 
{                
  0b00000000, 0b11100000,  
  0b01111001, 0b11111110,  
  0b11000000, 0b11100011,  
  0b10000000, 0b01100001,
  0b10000000, 0b00000001,
  0b10000000, 0b00000001,
  0b10000000, 0b00000001,
  0b11000000, 0b00000011, 
  0b01111111, 0b11111110,   
  0b00000000, 0b00000000,    
};
const unsigned char speedUpIcon[] PROGMEM = 
{               
  0b00000000, 0b00000000,
  0b11100000, 0b01110000,   
  0b00111000, 0b00011100,   
  0b00001110, 0b00000111,  
  0b00001110, 0b00000111,  
  0b00111000, 0b00011100,
  0b11100000, 0b01110000,  
  0b00000000, 0b00000000,       
};
const unsigned char speedDownIcon[] PROGMEM = 
{               
  0b00000000, 0b00000000,
  0b00001110, 0b00000111,   
  0b00111000, 0b00011100,   
  0b11100000, 0b01110000,  
  0b11100000, 0b01110000,  
  0b00111000, 0b00011100,
  0b00001110, 0b00000111,  
  0b00000000, 0b00000000,       
};
const unsigned char pitchUpIcon[] PROGMEM = 
{               
  0b11000011,
  0b11000011,
  0b11111111,
  0b11000011,
  0b11000011,
  0b11111111,
  0b11000011,
  0b11000011,
};
const unsigned char pitchDownIcon[] PROGMEM = 
{                 
  0b11000000,
  0b11000000,
  0b11000000,
  0b11000000,
  0b11111111,
  0b11000011,
  0b11000011,
  0b11111110,     
};
const unsigned char errorIcon16[] =
{
	0b00000000, 0b00000000, //                 
	0b00000011, 0b11100000, //       #####     
	0b00001111, 0b11111000, //     #########   
	0b00011111, 0b11111100, //    ###########  
	0b00111110, 0b00111110, //   #####   ##### 
	0b00111000, 0b01111110, //   ###    ###### 
	0b01110000, 0b11111111, //  ###    ########
	0b01110001, 0b11110111, //  ###   ##### ###
	0b01110011, 0b11000111, //  ###  ####   ###
	0b01110111, 0b10000111, //  ### ####    ###
	0b00111111, 0b00001110, //   ######    ### 
	0b00111110, 0b00011110, //   #####    #### 
	0b00011111, 0b11111100, //    ###########  
	0b00001111, 0b11111000, //     #########   
	0b00000011, 0b11100000, //       #####     
	0b00000000, 0b00000000, //                 
};
const unsigned char playIcon[] PROGMEM = 
{                          
  0b11100000, //             
  0b11111000, //           
  0b11111110, //            
  0b11111111, //            
  0b11111111, //            
  0b11111110, //            
  0b11111000, //            
  0b11100000, //   
};
const unsigned char pauseIcon[] PROGMEM = 
{               
  0b11100111,   
  0b11100111,   
  0b11100111,   
  0b11100111,   
  0b11100111,   
  0b11100111,   
  0b11100111,  
  0b11100111,       
};
const unsigned char stopIcon[] PROGMEM = 
{              
  0b11111111,   
  0b11111111,   
  0b11111111,   
  0b11111111,   
  0b11111111,   
  0b11111111,   
  0b11111111,  
  0b11111111,       
};
const unsigned char smallCross[] PROGMEM = 
{              
  0b11000011,   
  0b11100111,   
  0b01111110,   
  0b00111100,   
  0b00111100,   
  0b01111110,   
  0b11100111,  
  0b11000011,       
};
const unsigned char volumeIconOff[]  PROGMEM = 
{              
  0b00000100, 0b00000000, //                 
  0b00001100, 0b00000000, //                 
  0b00011100, 0b00000000, //                 
  0b11111100, 0b10010000, //                 
  0b11111100, 0b01100000, //                 
  0b11111100, 0b01100000, //                 
  0b11111100, 0b10010000, //                
  0b00011100, 0b00000000, //                 
  0b00001100, 0b00000000, //                 
  0b00000100, 0b00000000, //      
};
const unsigned char volumeIcons[][32]  PROGMEM = {
  {
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //                 
	  0b00000100, 0b00000000, //                 
	  0b00001100, 0b00000000, //                 
	  0b00011100, 0b00000000, //                 
	  0b11111100, 0b10010000, //                 
	  0b11111100, 0b01100000, //                 
	  0b11111100, 0b01100000, //                 
	  0b11111100, 0b10010000, //                
	  0b00011100, 0b00000000, //                 
	  0b00001100, 0b00000000, //                 
	  0b00000100, 0b00000000, //                       
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //      
  },
  {
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //                 
	  0b00000100, 0b00000000, //                 
	  0b00001100, 0b00000000, //                 
	  0b00011100, 0b00000000, //                 
	  0b11111101, 0b00000000, //                 
	  0b11111100, 0b10000000, //                 
	  0b11111100, 0b10000000, //                 
	  0b11111101, 0b00000000, //                
	  0b00011100, 0b00000000, //                 
	  0b00001100, 0b00000000, //                 
	  0b00000100, 0b00000000, //                       
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //      
  },
  {
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //                 
	  0b00000100, 0b00000000, //                 
	  0b00001100, 0b01000000, //                 
	  0b00011100, 0b00100000, //                 
	  0b11111101, 0b00010000, //                 
	  0b11111100, 0b10010000, //                 
	  0b11111100, 0b10010000, //                 
	  0b11111101, 0b00010000, //                
	  0b00011100, 0b00100000, //                 
	  0b00001100, 0b01000000, //                 
	  0b00000100, 0b00000000, //                       
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //      
  },
  {
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //                 
	  0b00000100, 0b00001000, //                 
	  0b00001100, 0b01000100, //                 
	  0b00011100, 0b00100010, //                 
	  0b11111101, 0b00010001, //                 
	  0b11111100, 0b10010001, //                 
	  0b11111100, 0b10010001, //                 
	  0b11111101, 0b00010001, //                
	  0b00011100, 0b00100010, //                 
	  0b00001100, 0b01000100, //                 
	  0b00000100, 0b00001000, //                       
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b00000000, //      
  },

};



const  unsigned char sectIconH[] PROGMEM = {      
	  0b00000000, 0b00000000, //                 
	  0b00011111, 0b11000000, //                 
	  0b00011111, 0b11111100, //                 
	  0b11111111, 0b11100100, //                 
	  0b11111111, 0b11100100, //                 
	  0b00011111, 0b11111100, //                 
	  0b00011111, 0b11000000, //                
	  0b00000000, 0b00000000, //   
};
const  unsigned char heart[] PROGMEM = {      
	  0b00000000, 0b00000000, //                 
	  0b00011100, 0b00111000, //                 
	  0b00111110, 0b01111100, //                 
	  0b01111111, 0b11111110, //                 
	  0b01111111, 0b11111110, //                 
	  0b01111111, 0b11111110, //                 
	  0b01111111, 0b11111110, //                
	  0b01111111, 0b11111110, //                  
	  0b00111111, 0b11111100, //                 
	  0b00011111, 0b11111000, //                 
	  0b00000111, 0b11100000, //                
	  0b00000001, 0b10000000, //   
};
const  unsigned char isOn[] PROGMEM = {      
	  0b00000000, 0b00000000, //    
	  0b01110000, 0b00001110, //               
	  0b01110000, 0b00001110, //               
	  0b00111000, 0b00011100, //               
	  0b00111000, 0b00011100, //               
	  0b00011100, 0b00111000, //               
	  0b00011100, 0b00111000, //               
	  0b00001110, 0b01110000, //               
	  0b00001110, 0b01110000, //               
	  0b00000111, 0b11100000, //               
	  0b00000111, 0b11000000, //               
	  0b00000000, 0b00000000, //              
};
const  unsigned char isOff[] PROGMEM = {       
	  0b00000000, 0b00000000, //                 
	  0b00111000, 0b00011100, //                 
	  0b00011100, 0b00111000, //              
	  0b00001110, 0b01110000, //               
	  0b00000111, 0b11100000, //               
	  0b00000011, 0b11000000, //               
	  0b00000011, 0b11000000, //               
	  0b00000111, 0b11100000, //               
	  0b00001110, 0b01110000, //                
	  0b00011100, 0b00111000, //                 
	  0b00111000, 0b00011100, //                 
	  0b00000000, 0b00000000, //   
};
const  unsigned char alimIcon[] PROGMEM = { 
	  0b00010000, //                 
	  0b00010000, //                 
	  0b00110000, //                 
	  0b00110000, //                 
	  0b00110000, //                 
	  0b01111110, //                
	  0b01111110, //                 
	  0b00001100, //                 
	  0b00001100, //                 
	  0b00001100, //                 
	  0b00001000, //                 
	  0b00001000, //    
};
const  unsigned char alimIconContour[] PROGMEM = { 
	  0b00101000, //                 
	  0b00101000, //                 
	  0b01001000, //                 
	  0b01001000, //                 
	  0b01001111, //                 
	  0b10000001, //                 
	  0b10000001, //                 
	  0b11110010, //                  
	  0b00010010, //                 
	  0b00010010, //                
	  0b00010100, //                 
	  0b00010100, //    
};
const  unsigned char alimIconH[] PROGMEM = {      
	  0b00000000, 0b00000000, //                 
	  0b00000000, 0b11000000, //                 
	  0b00000001, 0b11111000, //                 
	  0b01111001, 0b10011110, //                 
	  0b00011111, 0b10000000, //                 
	  0b00000011, 0b00000000, //                 
	  0b00000000, 0b00000000, //   
};
const  unsigned char alimIconContourH[] PROGMEM = {   
	  0b00000011, 0b11100000, //                 
	  0b00000011, 0b00111100, //                 
	  0b11111110, 0b00000111, //                 
	  0b10000110, 0b01100001, //                 
	  0b11100000, 0b01111111, //                 
	  0b00111100, 0b11000000, //                 
	  0b00000111, 0b11000000, //  
};

const  unsigned char sectIcon[] PROGMEM = {             
	0b00000110, 0b01100000, //      ##  ##     
	0b00000110, 0b01100000, //      ##  ##     
	0b00000110, 0b01100000, //      ##  ##     
	0b00000110, 0b01100000, //      ##  ##     
	0b00000110, 0b01100000, //      ##  ##      
	0b00011111, 0b11111000, //      ##  ##      
	0b00011111, 0b11111000, //      ##  ##      
	0b00011111, 0b11111000, //      ##  ##      
	0b00011111, 0b11111000, //      ##  ##      
	0b00011111, 0b11111000, //      ##  ##   
	0b00001111, 0b11110000, //      ##  ##  
	0b00001111, 0b11110000, //      ##  ##      
	0b00000111, 0b11100000, //      ##  ##      
	0b00000001, 0b10000000, //      ##  ##      
	0b00000001, 0b10000000, //      ##  ##      
	0b00000001, 0b10000000, //      ##  ##      
};
const unsigned char batLevelIcon[][32]  PROGMEM = {
  {                     
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, //       
	  0b00000000, 0b00000000, // 
	  0b11111111, 0b11111110, //                
	  0b11000000, 0b00000011, //                
	  0b11000000, 0b00000011, //                 
	  0b11000000, 0b00000011, //                
	  0b11000000, 0b00000011, //                
	  0b11000000, 0b00000011, //                
	  0b11000000, 0b00000011, //                
	  0b11000000, 0b00000011, //                 
	  0b11000000, 0b00000011, //               
	  0b11111111, 0b11111110, //   
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, //   
  },
  { 
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, // 
	  0b11111111, 0b11111110, //                
	  0b11000000, 0b00000011, //                
	  0b11011000, 0b00000011, //                 
	  0b11011000, 0b00000011, //                
	  0b11011000, 0b00000011, //                
	  0b11011000, 0b00000011, //                
	  0b11011000, 0b00000011, //                
	  0b11011000, 0b00000011, //               
	  0b11000000, 0b00000011, //               
	  0b11111111, 0b11111110, //  
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, //   
  },
  { 
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, // 
	  0b11111111, 0b11111110, //                
	  0b11000000, 0b00000011, //                
	  0b11011001, 0b10000011, //               
	  0b11011001, 0b10000011, //                
	  0b11011001, 0b10000011, //                
	  0b11011001, 0b10000011, //                
	  0b11011001, 0b10000011, //                
	  0b11011001, 0b10000011, //                  
	  0b11000000, 0b00000011, //               
	  0b11111111, 0b11111110, //    
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, // 
  },
  { 
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, // 
	  0b11111111, 0b11111110, //                
	  0b11000000, 0b00000011, //                
	  0b11011001, 0b10011011, //                
	  0b11011001, 0b10011011, //                
	  0b11011001, 0b10011011, //                
	  0b11011001, 0b10011011, //                
	  0b11011001, 0b10011011, //                
	  0b11011001, 0b10011011, //                 
	  0b11000000, 0b00000011, //               
	  0b11111111, 0b11111110, //    
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, // 
	  0b00000000, 0b00000000, // 
  },

};

