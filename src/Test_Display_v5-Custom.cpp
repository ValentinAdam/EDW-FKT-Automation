#include <Arduino.h>
#include "DisplayController.h"


#define Display_Columns 16
#define Display_Rows    2
#define Display_Address 0x3F


DisplayController displayLCD(Display_Columns, Display_Rows, Display_Address);


void setup() 
{
    Serial.begin(115200);
    displayLCD.initialize();
}


void loop() 
{
    displayLCD.printPASS();
    delay(3000);

    displayLCD.printFAIL();
    delay(3000);
}
