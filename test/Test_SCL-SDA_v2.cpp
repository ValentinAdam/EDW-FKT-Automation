// #include <Arduino.h>
// #include "DisplayController.h"
// #include "ColorDetector.h"

// #define PIN_Color_S0        21
// #define PIN_Color_S1        22
// #define PIN_Color_S2        2   //19
// #define PIN_Color_S3        15  //23
// #define PIN_Color_Out       18 
// #define PIN_Buzzer          26  //

// #define Display_Columns 16
// #define Display_Rows    2
// #define Display_Adress  0x3F

// // Create an instance of the DisplayController
// ColorDetector colorDetector(PIN_Color_S0, PIN_Color_S1, PIN_Color_S2, PIN_Color_S3, PIN_Color_Out);
// DisplayController displayLCD(Display_Columns, Display_Rows, Display_Adress);


// void setup() 
// {
//     Serial.begin(115200);
//     colorDetector.initialize();
//     displayLCD.initialize();
//     pinMode(PIN_Buzzer, OUTPUT);    //
//     delay(1000);
// }

// void loop() 
// {
//     Serial.println("Start program");
//     displayLCD.printFirstRow("Start program");
//     analogWrite(PIN_Buzzer, 0);  //
//     delay(2000);
//     analogWrite(PIN_Buzzer, 255);   //

//     int red_value = colorDetector.detectRed();
//     int green_value = colorDetector.detectGreen();
//     int blue_value = colorDetector.detectBlue();
//     Serial.println("Red = " + String(red_value) + "  Green = " + String(green_value) + "  Blue = " + String(blue_value));
//     displayLCD.printBothRows("R=" + String(red_value) + "  G=" + String(green_value), "B=" + String(blue_value));
//     delay(2000);

//     if(red_value > green_value && red_value > blue_value)   // TODO: Calibrate
//     {
//         Serial.println("RED LED ON");
//         displayLCD.printFirstRow("RED COLOR");       
//     }
//     else if (red_value > blue_value && green_value > blue_value)
//     {
//         Serial.println("YELLOW LED ON");
//         displayLCD.printFirstRow("YELLOW COLOR");
//     }
//     else
//     {
//         Serial.println("Unknown color");
//         displayLCD.printFirstRow("Unknown Color");
//     }

//     analogWrite(PIN_Buzzer, 0);  //
//     delay(2000);

// }
