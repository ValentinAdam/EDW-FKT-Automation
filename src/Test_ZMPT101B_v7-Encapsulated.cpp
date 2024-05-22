// #include <Arduino.h>
// #include "VoltageSensor.h"
// #include "Stepper.h"
// #define PIN_Stepper1            32
// #define PIN_Stepper2            33
// #define PIN_Stepper3            17
// #define PIN_Stepper4            16
// #define PIN_Voltmeter           36
// #define Voltage_Calibration     84
// #define Voltage_Phase_Shift     1.7
// #define Voltage_Measurements    80
// #define Voltage_Samples         80
// const double stepsPerRevolution = 200;                //    number of steps per revolution = 2037.8864    //  2048
// const double degreePerStep      = stepsPerRevolution/360;   //    celsius degree per step
// const double stepsLeftToRight   = -240*degreePerStep;        //    steps for 240 celsius degree
// const double stepsCenterToLeft  = 120*degreePerStep;       //    steps for 120 celsius degree
// const double stepsRightToCenter = 120*degreePerStep;       //    negative steps for 120 celsius degree
// const char* ssid = "EDW_CX_AP";
// const char* password = "89089455";

// Stepper myStepper(stepsPerRevolution, PIN_Stepper1, PIN_Stepper2, PIN_Stepper3, PIN_Stepper4);
// VoltageSensor voltage_monitor(PIN_Voltmeter, Voltage_Calibration, Voltage_Phase_Shift);

// void setup() 
// {
//     Serial.begin(115200);
// }

// void loop() 
// {
   
//     float voltage_value = voltage_monitor.measureVoltage(Voltage_Measurements, Voltage_Samples);
//     Serial.print("Average of last voltage values: ");
//     Serial.println(voltage_value);
    
// }
