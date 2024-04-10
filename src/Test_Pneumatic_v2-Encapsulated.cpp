// #include <Arduino.h>
// #include "PistonController.h"

// #define PIN_Piston1     17    // Brown
// #define PIN_Piston2     16    // Red
// #define PIN_Piston3     4    // Orange

// PistonController piston_controller(PIN_Piston1, PIN_Piston2, PIN_Piston3);

// void setup() 
// {
//     Serial.begin(115200);
//     piston_controller.initialize();
// }

// void loop() 
// {
//     piston_controller.retractPiston1();
//     piston_controller.retractPiston2();
//     piston_controller.retractPiston3();
//     delay(1000);
//     piston_controller.extendPiston1();
//     delay(2000);
//     piston_controller.retractPiston1();
//     piston_controller.extendPiston2();
//     delay(2000);
//     piston_controller.retractPiston2();
//     piston_controller.extendPiston3();    
//     delay(2000);
//     piston_controller.retractPiston1();
//     piston_controller.retractPiston2();
//     piston_controller.retractPiston3();
//     delay(2000);
//     piston_controller.extendPiston1();
//     piston_controller.extendPiston2();
//     delay(2000);
// }
