///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  //  Varianta 1 -- Originala
// #include <Arduino.h>
// #include "EmonLib.h"             // Include Emon Library

// // #define VOLT_CAL 148.7
// #define VOLT_CAL 75.71
// #define PIN_Voltmeter 13

// EnergyMonitor emon1;             // Create an instance

// void setup()
// {  
//     Serial.begin(115200);
//     emon1.voltage(PIN_Voltmeter, VOLT_CAL, 1.7);  // Voltage: input pin, calibration, phase_shift
// }

// void loop()
// {
//     // emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
//     emon1.calcVI(5,20);         // Calculate all. No.of half wavelengths (crossings), time-out
//     float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
//     Serial.println(supplyVoltage);
// }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////




// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  //  Varianta 2 -- cu -25 !!!!!!!!!!!!!!!!
// #include <Arduino.h>
// #include "EmonLib.h"             // Include Emon Library

// // #define VOLT_CAL 148.7
// #define VOLT_CAL        83.71
// #define Phase_shift     1.7
// #define PIN_Voltmeter   13

// EnergyMonitor emon1;             // Create an instance

// void setup()
// {  
//     Serial.begin(115200);
//     emon1.voltage(PIN_Voltmeter, VOLT_CAL, Phase_shift);  // Voltage: input pin, calibration, phase_shift
// }

// void loop()
// {
//     emon1.calcVI(5,20);         // Calculate all. No.of half wavelengths (crossings), time-out
//     float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
//     Serial.println(supplyVoltage-float(25));
// }
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  //  Varianta 3 -- Aproape buna la 100, proasta la celelalte
// #include <Arduino.h>
// #include "EmonLib.h"             // Include Emon Library

// // #define VOLT_CAL 148.7
// #define VOLT_CAL 68.71
// #define PIN_Voltmeter 13

// EnergyMonitor emon1;             // Create an instance

// void setup()
// {  
//     Serial.begin(115200);
//     emon1.voltage(PIN_Voltmeter, VOLT_CAL, 1.7);  // Voltage: input pin, calibration, phase_shift
// }

// void loop()
// {
//     emon1.calcVI(5,20);         // Calculate all. No.of half wavelengths (crossings), time-out
//     float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
//     Serial.println(supplyVoltage);
// }
// //  100 --> 105
// //  163 --> 152
// //  224 --> 205
///////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  //  Varianta 4 -- ???
// #include <Arduino.h>
// #include "EmonLib.h"             // Include Emon Library

// // #define VOLT_CAL 148.7
// #define VOLT_CAL 70.71
// #define PIN_Voltmeter 13

// EnergyMonitor emon1;             // Create an instance

// void setup()
// {  
//     Serial.begin(115200);
//     emon1.voltage(PIN_Voltmeter, VOLT_CAL, 1.7);  // Voltage: input pin, calibration, phase_shift
// }

// void loop()
// {
//     emon1.calcVI(5,20);         // Calculate all. No.of half wavelengths (crossings), time-out
//     float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
//     Serial.println(supplyVoltage);
// }
// //  100 --> 106
// //  160 --> 155
// //  224 --> 212
///////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //  //  Varianta 5 -- ???
// #include <Arduino.h>
// #include "EmonLib.h"             // Include Emon Library

// // #define VOLT_CAL 148.7
// #define VOLT_CAL 71.25
// #define PIN_Voltmeter 13

// EnergyMonitor emon1;             // Create an instance

// void setup()
// {  
//     Serial.begin(115200);
//     emon1.voltage(PIN_Voltmeter, VOLT_CAL, 1.7);  // Voltage: input pin, calibration, phase_shift
// }

// void loop()
// {
//     emon1.calcVI(5,20);         // Calculate all. No.of half wavelengths (crossings), time-out
//     float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
//     Serial.println(supplyVoltage);
// }
// //  100 --> 108
// //  163 --> 157
// //  223 --> 213
///////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  //  Varianta 6 -- 
// #include <Arduino.h>
// #include "EmonLib.h"             // Include Emon Library

// // #define VOLT_CAL 148.7
// #define VOLT_CAL 111.11
// #define PIN_Voltmeter 13

// EnergyMonitor emon1;             // Create an instance

// void setup()
// {  
//     Serial.begin(115200);
//     emon1.voltage(PIN_Voltmeter, VOLT_CAL, 1.7);  // Voltage: input pin, calibration, phase_shift
// }

// void loop()
// {
//     emon1.calcVI(5,20);         // Calculate all. No.of half wavelengths (crossings), time-out
//     float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
//     Serial.println(supplyVoltage-float(25));
// }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////