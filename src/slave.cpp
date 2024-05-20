// #include <Arduino.h>
// #include "ColorDetector.h"
// #include "ButtonCounter.h"
// #include "VoltageSensor.h"
// #include "Stepper.h"
// #include "WiFi.h"
// #include "ESPAsyncWebServer.h"

// #define PIN_Stepper1            32
// #define PIN_Stepper2            33
// #define PIN_Stepper3            17
// #define PIN_Stepper4            16
// #define PIN_Color_S0            18
// #define PIN_Color_S1            19
// #define PIN_Color_S2            5
// #define PIN_Color_S3            23
// #define PIN_Color_Out           39
// #define PIN_Voltmeter           36
// #define PIN_Optical_Count       34
// #define PIN_Microswitch         21
// #define PIN_RegionSel           4

// #define Volt_Min_UE_ll          95
// #define Volt_Min_UE_lh          107
// #define Volt_Min_US_ll          49
// #define Volt_Min_US_lh          59
// #define Volt_Max_UE_ll          220
// #define Volt_Max_UE_lh          232
// #define Volt_Max_US_ll          112
// #define Volt_Max_US_lh          122

// #define Button_Count_Limit_Presses      10
// #define Button_Count_Limit_Time         30000
// #define Voltage_Calibration             84
// #define Voltage_Phase_Shift             1.7
// #define Voltage_Measurements            80
// #define Voltage_Samples                 20
// int min_ll = 0;
// int min_lh = 0;
// int max_ll = 0;
// int max_lh = 0; 

// const double stepsPerRevolution = 200;                //    number of steps per revolution = 2037.8864    //  2048
// const double degreePerStep      = stepsPerRevolution/360;   //    celsius degree per step
// const double stepsLeftToRight   = -240*degreePerStep;        //    steps for 240 celsius degree
// const double stepsCenterToLeft  = 120*degreePerStep;       //    steps for 120 celsius degree
// const double stepsRightToCenter = 120*degreePerStep;       //    negative steps for 120 celsius degree
// const char* ssid = "EDW_CX_AP";
// const char* password = "89089455";

// Stepper myStepper(stepsPerRevolution, PIN_Stepper1, PIN_Stepper2, PIN_Stepper3, PIN_Stepper4);
// ColorDetector colorDetector(PIN_Color_S0, PIN_Color_S1, PIN_Color_S2, PIN_Color_S3, PIN_Color_Out);
// VoltageSensor voltage_monitor(PIN_Voltmeter, Voltage_Calibration, Voltage_Phase_Shift);
// ButtonCounter opticalCounter(PIN_Optical_Count);
// AsyncWebServer server(80);
// const String pass = "PASS";
// const String fail = "FAIL";

// String potCalib()
//     {
//         Serial.println("Beginning searching the zero point");
//         int microswitch_state = digitalRead(PIN_Microswitch);
//         Serial.println("Microswitch state is: " + String(microswitch_state));
//         unsigned long time_of_searching_zero = millis();
//         const int stop_searching_zero = 10000;  // 10 secunde
//         bool error_searching_zero = false;
//         while(microswitch_state == HIGH)
//         {
//             Serial.println("Microswitch not pressed");
//             myStepper.step(-10);
//             Serial.println("Stepper motor moved 1 step to the right");
//             int microswitch_state_check = digitalRead(PIN_Microswitch);
//             if(microswitch_state_check == LOW)
//             {
//                 Serial.println("Microswitch is pressed");
//                 delay(150);
//                 myStepper.step(stepsRightToCenter);
//                 return pass;
//             }
//             if (millis() - time_of_searching_zero >= stop_searching_zero)
//             {
//                 Serial.println("Timeout: " + String(stop_searching_zero/1000) + " seconds have elapsed since started searching for zero point");
//                 error_searching_zero = true;
//                 return fail;
//             }
//         }
//         if(error_searching_zero == true)
//         {
//             Serial.println("Microswitch not pressed. TURN MAIN POWER OFF !!!");
//             return fail;
//         }
//     }

// String checkRedLed()
// {
//     unsigned long time_of_checking_led_red = millis();
//     const int stop_searching_led_red = 10000;  // 10 secunde
//     bool error_searching_led_RED = false;
//     while(true)
//     {
//         int red_value1 = colorDetector.detectRed();
//         int green_value1 = colorDetector.detectGreen();
//         int blue_value1 = colorDetector.detectBlue();
//         Serial.println("Red = " + String(red_value1) + "  Green = " + String(green_value1) + "  Blue = " + String(blue_value1));
//         if(red_value1 > green_value1 && red_value1 > blue_value1)   // TODO: Calibrate and change to 0-255
//         {
//             Serial.println("RED LED ON");
//             return pass;
//         }
//         else if (red_value1 > blue_value1 && green_value1 > blue_value1)
//         {
//             Serial.println("YELLOW LED ON");
//             return fail;
//         }
//         if (millis() - time_of_checking_led_red >= stop_searching_led_red) 
//         {
//             Serial.println("Timeout: " + String(stop_searching_led_red/1000) + " seconds have elapsed since started checking if LED is RED");
//             return fail;
//         }
//     }
// }

// String checkMinVolt()
//     {
//         myStepper.step(stepsCenterToLeft);
//         delay(150);
//         float voltage_value_MIN = voltage_monitor.measureVoltage(Voltage_Measurements, Voltage_Samples);
//         if(voltage_value_MIN > min_ll && voltage_value_MIN < min_lh)
//         {
//             myStepper.step(stepsLeftToRight);
//             return pass;
//         }
//         else
//         {
//             myStepper.step(stepsLeftToRight);
//             return fail;
//         }
//     }

// String checkMaxVolt()
//     {
//         float voltage_value_MAX = voltage_monitor.measureVoltage(Voltage_Measurements, Voltage_Samples);
//         if(voltage_value_MAX >= max_ll && voltage_value_MAX <= max_lh)
//         {
//             myStepper.step(stepsRightToCenter);
//             return pass;
//         }
//         else
//         {
//             myStepper.step(stepsRightToCenter);
//             return fail;
//         }
//     }

// String checkYellowLed()
// {
//     unsigned long time_of_checking_led_yellow = millis();
//     const int stop_searching_led_yellow = 10000;  // 10 secunde
//     bool error_searching_led_YELLOW = false;
//     while(true)
//     {
//         int red_value2 = colorDetector.detectRed();
//         int green_value2 = colorDetector.detectGreen();
//         int blue_value2 = colorDetector.detectBlue();
//         Serial.println("Red = " + String(red_value2) + "  Green = " + String(green_value2) + "  Blue = " + String(blue_value2));
//         if(red_value2 > green_value2 && red_value2 > blue_value2)   // TODO: Calibrate and change to 0-255
//         {
//             Serial.println("RED LED ON");
//             return fail;
//         }
//         else if (red_value2 > blue_value2 && green_value2 > blue_value2)
//         {
//             Serial.println("YELLOW LED ON");
//             return pass;
//         }
//         if (millis() - time_of_checking_led_yellow >= stop_searching_led_yellow) 
//         {
//             Serial.println("Timeout: " + String(stop_searching_led_yellow/1000) + " seconds have elapsed since started checking if LED is RED");
//             return fail;
//         }
//     }
// }

// String checkSyncromotor()
// {
//     bool checking_optical_rotation = opticalCounter.countButtonPresses(Button_Count_Limit_Presses, Button_Count_Limit_Time);
//         if (checking_optical_rotation == true) 
//         {
//             Serial.println("Synchronmotor successfully rotated!");
//             return pass;
//         }
//         else
//         {
//             Serial.println("Error. Time expired. Button not pressed successfully");
//             return fail;
//         }
// }

// void setup()
// {
//     Serial.begin(115200);
//     myStepper.setSpeed(60);   //  stepper speed in rpm
//     colorDetector.initialize();
//     opticalCounter.initialize();
//     pinMode(PIN_Microswitch, INPUT_PULLUP);
//     pinMode(PIN_RegionSel, INPUT_PULLUP);
//     if(PIN_RegionSel == HIGH)//pentru unitatile cu destinatia UE pinul va ramane neconectat(cel mai intalnit)
//     {
//          min_ll = Volt_Min_UE_ll;
//          min_lh = Volt_Min_UE_lh;
//          max_ll = Volt_Max_UE_ll;
//          max_lh = Volt_Max_UE_lh;
//     }
//     else
//     {
//          min_ll = Volt_Min_US_ll;
//          min_lh = Volt_Min_US_lh;
//          max_ll = Volt_Max_US_ll;
//          max_lh = Volt_Max_US_lh;
//     }
//     Serial.println(min_ll);
//     Serial.println(min_lh);
//     Serial.println(max_ll);
//     WiFi.softAP(ssid, password);
//     IPAddress IP = WiFi.softAPIP();
    
//     server.on("/calibrate", HTTP_GET, [](AsyncWebServerRequest *request)
//     {
//     request->send_P(200, "text/plain", potCalib().c_str());
//     });

//     server.on("/redled", HTTP_GET, [](AsyncWebServerRequest *request)
//     {
//     request->send_P(200, "text/plain", checkRedLed().c_str());
//     });

//     server.on("/minimumvoltage", HTTP_GET, [](AsyncWebServerRequest *request)
//     {
//     request->send_P(200, "text/plain", checkMinVolt().c_str());
//     });

//     server.on("/maximumvoltage", HTTP_GET, [](AsyncWebServerRequest *request)
//     {
//     request->send_P(200, "text/plain", checkMaxVolt().c_str());
//     });

//     server.on("/yellowled", HTTP_GET, [](AsyncWebServerRequest *request)
//     {
//     request->send_P(200, "text/plain", checkYellowLed().c_str());
//     });

//     server.on("/synchromotor", HTTP_GET, [](AsyncWebServerRequest *request)
//     {
//     request->send_P(200, "text/plain", checkSyncromotor().c_str());
//     });

//     server.begin();
// }
// void loop()
// {    
// }




