/**********************
* Externes Libraries 
***********************/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SdFat.h>
#include <Adafruit_VS1053.h>

/**********************
* CONFIG
***********************/
#include "Config.h"
#include "Icons.h"

/**********************
* Local Classes & Functions
***********************/
#include "libs/Class.Pitcher.h"
#include "libs/Class.Path.h"
#include "libs/Class.FilePicker.h"
#include "libs/Class.SleepWatch.h"
#include "libs/Class.Multiplex.h"
#include "libs/Class.ButtonHandler.h"
#include "libs/Class.Rotary.h"
#include "Class.Display.h"
#include "Class.Debug.h"

/**********************
* INIT
***********************/
#include "Init.h"
/**********************
* Display
***********************/
/**********************
* MAIN LOGIC
***********************/

#include "Events.h"
#include "Setup.h"
#include "Loop.h"