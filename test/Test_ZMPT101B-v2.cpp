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