// #include <Arduino.h>
// #include "ColorDetector.h"
// #include "PistonController.h"

// #define PIN_Color_S0         23
// #define PIN_Color_S1         22
// #define PIN_Color_S2         19
// #define PIN_Color_S3         21
// #define PIN_Color_Out        18
// #define PIN_Relay               27
// #define PIN_Piston1             17      // Brown
// #define PIN_Piston2             16      // Red
// #define PIN_Piston3             4       // Orange

// ColorDetector colorDetector(PIN_Color_S0, PIN_Color_S1, PIN_Color_S2, PIN_Color_S3, PIN_Color_Out);
// PistonController piston_controller(PIN_Piston1, PIN_Piston2, PIN_Piston3);

// void setup()
// {
//     Serial.begin(115200);
//     colorDetector.initialize();
//     piston_controller.initialize();
//     pinMode(PIN_Relay, OUTPUT);
//     analogWrite(PIN_Relay, 0);
//     piston_controller.retractPiston1();
//     piston_controller.retractPiston2();
//     piston_controller.retractPiston3();

//     piston_controller.extendPiston1();
//     analogWrite(PIN_Relay, 255);
//     delay(2500);
//     piston_controller.retractPiston1();
    
// }

// void loop()
// {
//     int red_value = colorDetector.detectRed();
//     int green_value = colorDetector.detectGreen();
//     int blue_value = colorDetector.detectBlue();
//     Serial.println("Red = " + String(red_value) + "  Green = " + String(green_value) + "  Blue = " + String(blue_value));

//     if(red_value > green_value && red_value > blue_value)   // TODO: Calibrate
//     // if(red_value < green_value && red_value < blue_value)
//     {
//         Serial.println("RED LED ON");
//     }
//     else if (red_value > blue_value && green_value > blue_value)
//     // else if (red_value < blue_value && green_value < blue_value)
//     {
//         Serial.println("YELLOW LED ON");
//     }
//     else
//     {
//         Serial.println("Unknown color");
//     }

//     delay(1000);
// }
