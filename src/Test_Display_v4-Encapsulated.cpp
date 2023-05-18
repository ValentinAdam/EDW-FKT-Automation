// #include <Arduino.h>
// #include "DisplayController.h"

// #define Display_Columns 16
// #define Display_Rows    2
// #define Display_Adress  0x3F

// // Create an instance of the DisplayController
// DisplayController displayLCD(Display_Columns, Display_Rows, Display_Adress);

// const float test = 123.45F;
// const double test2 = 678.99;

// void setup() 
// {
//     Serial.begin(115200);
//     displayLCD.initialize();
// }

// void loop() 
// {
//     // Print on first row only
//     displayLCD.printFirstRow("Test1: " + String(test));
//     delay(2000);

//     // Print on second row only
//     displayLCD.printSecondRow("Test2: " + String(test2));
//     delay(2000);

//     // Print on both rows
//     displayLCD.printBothRows("Test1: " + String(test), "Test2: " + String(test2));
//     delay(2000);
// }
