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
//     int number_of_measurements = 50;
//     int number_of_values_selected = 20;
//     float measurements[number_of_measurements];  // Array to store all measured values
//     int count = 0;            // Variable to keep track of the number of measurements

//     for (int i = 0; i < number_of_measurements; i++)
//     {
//         emon1.calcVI(5, 20);          // Calculate voltage and current measurements
//         float supplyVoltage = emon1.Vrms;  // Extract the RMS voltage value

//         measurements[i] = supplyVoltage;  // Store the measured value in the array
//         count++;                          // Increment the count

//         // delay(10);             // Delay for stability (adjust if necessary)
//     }

//     // Calculate the sum of the last values
//     float sum = 0.0;
//     for (int i = count - number_of_values_selected; i < count; i++)
//     {
//         sum += measurements[i];
//     }

//     float average = (sum / float(number_of_values_selected)) - 25.0;  // Calculate the average of the last 20 values

//     Serial.print("Average of last values: ");
//     Serial.println(average);

//     // delay(1000);  // Delay before starting the next iteration
// }
