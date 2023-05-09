// #include <Arduino.h>
// #include "ColorDetector.h"

// #define PIN_Color_S0         23
// #define PIN_Color_S1         22
// #define PIN_Color_S2         19
// #define PIN_Color_S3         21
// #define PIN_Color_Out        18

// ColorDetector colorDetector(PIN_Color_S0, PIN_Color_S1, PIN_Color_S2, PIN_Color_S3, PIN_Color_Out);

// void setup()
// {
//     Serial.begin(115200);
//     colorDetector.initialize();
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
