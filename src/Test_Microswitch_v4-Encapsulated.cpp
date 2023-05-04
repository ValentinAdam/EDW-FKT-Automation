// #include <Arduino.h>
// #include "ButtonCounter.h"

// #define PIN_Button_Count 13

// ButtonCounter myButtonCounter(PIN_Button_Count);

// void setup() 
// {
//     Serial.begin(115200);
//     pinMode(PIN_Button_Count, INPUT_PULLUP);
// }

// void loop() 
// {
//     Serial.println("START OF THE PROGRAM");
//     delay(2000);

//     if(myButtonCounter.countButtonPresses(10, 30000))
//     {
//         Serial.println("Flag is on!");
//     }

//     Serial.println("END OF THE PROGRAM");
//     delay(2000);
// }