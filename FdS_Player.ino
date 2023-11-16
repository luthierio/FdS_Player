/**********************
* Externes Libraries 
***********************/
#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#include <SdFat.h>
#define PREFER_SDFAT_LIBRARY 1
#include <Adafruit_VS1053.h>

#include "inc/Icons.h"

/**********************
* CONFIG
***********************/
#include "Config.h"

/**********************
* Local Classes & Functions
***********************/
#include "libs/Class.FdS_Adafruit_VS1053.h"
#include "libs/Class.Pitcher.h"
#include "libs/Class.Path.h"
#include "libs/Class.FilePicker.h"
#include "libs/Class.SleepWatch.h"
#include "libs/Class.Multiplex.h"
#include "libs/Class.ButtonHandler.h"
#include "libs/Class.Rotary.h"
#include "libs/Class.Debug.h"
#include "libs/Class.FileManager.h"
#include "Class.Markers.h"
#include "Class.PlayerDisplay.h"

/**********************
* INIT
***********************/
#include "Init.h"
#include "Utils.h"
/**********************
* Display
***********************/
/**********************
* MAIN LOGIC
***********************/

#include "Events.h"
#include "Setup.h"
#include "Loop.h"