#include "LedControl.h"
#include "MAX7219.h"
#include <Wire.h>

MAX7219 lc = MAX7219(9, 11, 10, 1);

void setup()
{
	lc.shutdown(0, false);
	lc.setIntensity(0, 10);
	lc.clearDisplay(0);
	
	Wire.begin();
}

void loop()
{


  lc.clearDisplay(0);


  for(int address = 1; address <= 999; address++ ) 
  {
		lc.display(address);
		delay(50);
    
  }

  //delay(5000);
}
