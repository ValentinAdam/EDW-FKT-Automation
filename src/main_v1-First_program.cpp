// #include <Arduino.h>
// #include "ColorDetector.h"
// #include "DisplayController.h"
// #include "ButtonCounter.h"
// #include "PistonController.h"
// #include "VoltageSensor.h"
// #include "Stepper.h"


// #define PIN_Stepper1            32
// #define PIN_Stepper2            33
// #define PIN_Stepper3            25
// #define PIN_Stepper4            26
// #define PIN_Color_S0            21
// #define PIN_Color_S1            22
// #define PIN_Color_S2            2
// #define PIN_Color_S3            15
// #define PIN_Color_Out           34
// #define PIN_Voltmeter           35
// #define PIN_Piston1             17      // Brown
// #define PIN_Piston2             16      // Red
// #define PIN_Piston3             4       // Orange
// #define PIN_Optical_Count       19
// #define PIN_Microswitch         18
// #define PIN_Relay               13
// #define PIN_Door                14
// #define PIN_Button_Fail_LED     12      // Same
// #define PIN_Button_Fail_Switch  27
// #define PIN_Buzzer              23
// #define PIN_LED_Red             12      // Same
// #define PIN_LED_Green           5


// #define Display_Columns                 16
// #define Display_Rows                    2
// #define Display_Address                 0x3F
// #define Button_Count_Limit_Presses      10
// #define Button_Count_Limit_Time         30000
// #define Voltage_Calibration             84
// #define Voltage_Phase_Shift             1.7
// #define Voltage_Measurements            80
// #define Voltage_Samples                 20


// const double stepsPerRevolution = 2037.8864;                //    number of steps per revolution = 2037.8864
// const double degreePerStep      = stepsPerRevolution/360;   //    celsius degree per step
// const double stepsLeftToRight   = 240*degreePerStep;        //    steps for 240 celsius degree
// const double stepsCenterToLeft  = -120*degreePerStep;       //    steps for 120 celsius degree
// const double stepsRightToCenter = -120*degreePerStep;       //    negative steps for 120 celsius degree


// Stepper myStepper(stepsPerRevolution, PIN_Stepper1, PIN_Stepper3, PIN_Stepper2, PIN_Stepper4);
// ColorDetector colorDetector(PIN_Color_S0, PIN_Color_S1, PIN_Color_S2, PIN_Color_S3, PIN_Color_Out);
// VoltageSensor voltage_monitor(PIN_Voltmeter, Voltage_Calibration, Voltage_Phase_Shift);
// PistonController piston_controller(PIN_Piston1, PIN_Piston2, PIN_Piston3);
// ButtonCounter opticalCounter(PIN_Optical_Count);
// DisplayController displayLCD(Display_Columns, Display_Rows, Display_Address);


// void setup()
// {
//     Serial.begin(115200);
//     myStepper.setSpeed(15);   //  stepper speed in rpm
//     colorDetector.initialize();
//     piston_controller.initialize();
//     opticalCounter.initialize();
//     pinMode(PIN_Microswitch, INPUT_PULLUP);
//     displayLCD.initialize();
//     pinMode(PIN_Relay, OUTPUT);
//     pinMode(PIN_Door, INPUT_PULLUP);
//     pinMode(PIN_Button_Fail_Switch, INPUT_PULLUP);
//     pinMode(PIN_Button_Fail_LED, OUTPUT);
//     pinMode(PIN_Buzzer, OUTPUT);
//     pinMode(PIN_LED_Red, OUTPUT);
//     pinMode(PIN_LED_Green, OUTPUT);

//     analogWrite(PIN_Relay, 0);
//     analogWrite(PIN_Button_Fail_LED, 0);
//     analogWrite(PIN_Buzzer, 0);
//     analogWrite(PIN_LED_Red, 0);
//     analogWrite(PIN_LED_Green, 0);
//     piston_controller.retractPiston1();
//     piston_controller.retractPiston2();
//     piston_controller.retractPiston3();
// }


// void loop()
// {
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Pornire aparat (Se comuta buton "Main Power")       -->     Verificare senzor usa deschisa                      (BUTON USA)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_check_door_open:
//     {
//         int door_open_state = digitalRead(PIN_Door);
//         Serial.println("Door state is: " + String(door_open_state));
//         Serial.println("Checking if door is open");
//         if(door_open_state == LOW)
//         {
//             Serial.println("Door is closed !!!");
//             analogWrite(PIN_Buzzer, 255);
//             analogWrite(PIN_LED_Red, 255);
//             goto state_check_door_open;
//         }
//         else
//         {
//             Serial.println("Door is open !!!");
//             analogWrite(PIN_Buzzer, 0);
//             analogWrite(PIN_LED_Red, 0);
//             goto state_search_zero;        
//         }
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare senzor usa deschisa                 -->     Rotire potentiometru spre "0"                       (STEPPER MOTOR)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    In timpul rotirii potentiometrului                  -->     Verificare pozitie de "0"                           (MICROSWITCH)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_search_zero:
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
//             myStepper.step(1);
//             Serial.println("Stepper motor moved 1 step to the right");
//             int microswitch_state_check = digitalRead(PIN_Microswitch);
//             if(microswitch_state_check == LOW)
//             {
//                 Serial.println("Microswitch is pressed");
//                 goto state_center_potentiometer;
//             }
//             if (millis() - time_of_searching_zero >= stop_searching_zero) 
//             {
//                 Serial.println("Timeout: " + String(stop_searching_zero/1000) + " seconds have elapsed since started searching for zero point");
//                 error_searching_zero = true;
//                 break;
//             }
//         }
//         while(error_searching_zero == true)
//         {
//             Serial.println("Microswitch not pressed. TURN MAIN POWER OFF !!!");
//             analogWrite(PIN_Buzzer, 255);
//             analogWrite(PIN_LED_Red, 255);         
//         }
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa atingere pozitie de "0"                        -->     Centrare potentiometru                              (STEPPER MOTOR)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_center_potentiometer:
//     {
//         Serial.println("Moving potentiometer into central position");
//         myStepper.step(stepsRightToCenter);
//         goto state_confirm_initialization;
//     }    
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa centrare potentiometru                         -->     Activare LED verde confirmare initializare          (LED VERDE)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_confirm_initialization:
//     {
//         analogWrite(PIN_LED_Green, 255);
//         Serial.println("Potentiometer centered. Green LED ON");
//         goto state_check_door_closed;
//     }

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa confirmare initializare cu succes              -->     Verificare senzor usa inchisa                       (SENZOR USA)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_check_door_closed:
//     {
//         analogWrite(PIN_LED_Green, 0);
//         int door_closed_state = digitalRead(PIN_Door);
//         Serial.println("Door state is: " + String(door_closed_state));
//         Serial.println("Checking if door is closed");
//         unsigned long time_of_checking_door_closed = millis();
//         const int stop_searching_door_closed = 10000;  // 10 secunde
//         bool error_searching_door_closed = false;
//         while(door_closed_state == LOW)
//         {
//             Serial.println("Door is open");
//             int door_closed_state_check = digitalRead(PIN_Door);
//             if(door_closed_state_check == HIGH)
//             {
//                 Serial.println("Door is closed");
//                 goto state_activate_piston1;
//             }
//             if (millis() - time_of_checking_door_closed >= stop_searching_door_closed) 
//             {
//                 Serial.println("Timeout: " + String(stop_searching_door_closed/1000) + " seconds have elapsed since started checking if door is closed");
//                 error_searching_door_closed = true;
//                 break;
//             }
//         }
//         while(error_searching_door_closed == true)
//         {
//             Serial.println("Door not closed. PRESS CONFIRM FAIL & CLOSE THE DOOR !!!");
//             analogWrite(PIN_Buzzer, 255);
//             analogWrite(PIN_LED_Red, 255);
//             analogWrite(PIN_Button_Fail_LED, 255);
//             if(digitalRead(PIN_Button_Fail_Switch) == HIGH)
//             {
//                 Serial.println("Fail confirmed");
//                 goto state_check_door_closed;
//             }         
//         }
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare usa inchisa                         -->     Activare piston "Pruftaste"                         (PISTON 1)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_activate_piston1:
//     {
//         piston_controller.extendPiston1();
//         Serial.println("Piston 1 activated");
//         goto state_boardpower_activate;
//     }    
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa activare piston "Pruftaste"                    -->     Comutare releu "Boardpower"                         (RELEU BOARDPOWER)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_boardpower_activate:
//     {
//         analogWrite(PIN_Relay, HIGH);
//         Serial.println("Boardpower activated");
//         goto state_check_LED_RED;
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa comutare releu "Boardpower"                    -->     Verificare culoare rosie LED                        (SENZOR CULOARE)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_check_LED_RED:
//     {
//         unsigned long time_of_checking_led_red = millis();
//         const int stop_searching_led_red = 10000;  // 10 secunde
//         bool error_searching_led_RED = false;
//         while(true)
//         {
//             int red_value1 = colorDetector.detectRed();
//             int green_value1 = colorDetector.detectGreen();
//             int blue_value1 = colorDetector.detectBlue();
//             Serial.println("Red = " + String(red_value1) + "  Green = " + String(green_value1) + "  Blue = " + String(blue_value1));
//             if(red_value1 > green_value1 && red_value1 > blue_value1)   // TODO: Calibrate and change to 0-255
//             {
//                 Serial.println("RED LED ON");
//                 goto state_deactivate_piston1;
//             }
//             else if (red_value1 > blue_value1 && green_value1 > blue_value1)
//             {
//                 Serial.println("YELLOW LED ON");
//             }
//             else
//             {
//                 Serial.println("Unknown color");
//             }

//             if (millis() - time_of_checking_led_red >= stop_searching_led_red) 
//             {
//                 Serial.println("Timeout: " + String(stop_searching_led_red/1000) + " seconds have elapsed since started checking if LED is RED");
//                 error_searching_led_RED = true;
//                 piston_controller.retractPiston1();
//                 Serial.println("Piston 1 deactivated");            
//                 break;
//             }
//         }

//         while(error_searching_led_RED == true)
//         {
//             Serial.println("RED LED not detected. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
//             analogWrite(PIN_Buzzer, 255);
//             analogWrite(PIN_LED_Red, 255);
//             analogWrite(PIN_Button_Fail_LED, 255);
//             if(digitalRead(PIN_Button_Fail_Switch) == HIGH)
//             {
//                 Serial.println("Fail confirmed");
//                 goto state_boardpower_deactivate;
//             }         
//         }
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare LED rosu                            -->     Dezactivare piston "Pruftaste"                      (PISTON 1)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_deactivate_piston1:
//     {
//         piston_controller.retractPiston1();
//         Serial.println("Piston 1 deactivated");
//         goto state_stepper_to_min;
//     }     
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa dezactivare piston "Pruftaste"                 -->     Rotire stepper in pozitia MIN                       (STEPPER)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_stepper_to_min:
//     {
//         Serial.println("Moving stepper to MIN voltage position...");
//         myStepper.step(stepsCenterToLeft);
//         Serial.println("Stepper reached MIN voltage position...");
//         goto state_voltage_check_MIN;
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa rotire stepper la MIN                          -->     Verificare senzor tensiune MIN                      (ZMPT101B)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_voltage_check_MIN:
//     {
//         bool error_checking_voltage_MIN = false;
//         float voltage_value_MIN = voltage_monitor.measureVoltage(Voltage_Measurements, Voltage_Samples);
//         Serial.println("Average of last voltage values: " + String(voltage_value_MIN));
//         if(voltage_value_MIN > 94 && voltage_value_MIN < 108)
//         {
//             Serial.println("MIN voltage value OK");
//             goto state_stepper_to_max;
//         }
//         else
//         {
//             Serial.println("MIN voltage value NOT OK");
//             error_checking_voltage_MIN = true;
//         }

//         while(error_checking_voltage_MIN == true)
//         {
//             Serial.println("MIN voltage value NOT OK. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
//             analogWrite(PIN_Buzzer, 255);
//             analogWrite(PIN_LED_Red, 255);
//             analogWrite(PIN_Button_Fail_LED, 255);
//             if(digitalRead(PIN_Button_Fail_Switch) == HIGH)
//             {
//                 Serial.println("Fail confirmed");
//                 goto state_boardpower_deactivate;
//             }         
//         }
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare valoare MIN                         -->     Rotire stepper in pozitia MAX                       (STEPPER)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_stepper_to_max:
//     {
//         Serial.println("Moving stepper to MAX voltage position...");
//         myStepper.step(stepsLeftToRight);
//         Serial.println("Stepper reached MAX voltage position...");
//         goto state_voltage_check_MAX;
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa rotire stepper la MAX                          -->     Verificare senzor tensiune MAX                      (ZMPT101B)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_voltage_check_MAX:
//     {
//         bool error_checking_voltage_MAX = false;
//         float voltage_value_MAX = voltage_monitor.measureVoltage(Voltage_Measurements, Voltage_Samples);
//         Serial.println("Average of last voltage values: " + String(voltage_value_MAX));
//         if(voltage_value_MAX > 219 && voltage_value_MAX < 233)
//         {
//             Serial.println("MAX voltage value OK");
//             goto state_stepper_to_center;
//         }
//         else
//         {
//             Serial.println("MAX voltage value NOT OK");
//             error_checking_voltage_MAX = true;
//         }

//         while(error_checking_voltage_MAX == true)
//         {
//             Serial.println("MAX voltage value NOT OK. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
//             analogWrite(PIN_Buzzer, 255);
//             analogWrite(PIN_LED_Red, 255);
//             analogWrite(PIN_Button_Fail_LED, 255);
//             if(digitalRead(PIN_Button_Fail_Switch) == HIGH)
//             {
//                 Serial.println("Fail confirmed");
//                 goto state_boardpower_deactivate;
//             }         
//         }
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare valoare MAX                         -->     Centrare stepper                                    (STEPPER)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_stepper_to_center:
//     {
//         Serial.println("Moving stepper to CENTER position...");
//         myStepper.step(stepsRightToCenter);
//         Serial.println("Stepper reached CENTER position...");
//         goto state_activate_piston2;
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa centrare stepper                               -->     Activare piston "Abreinigung"                       (PISTON 2)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_activate_piston2:
//     {
//         piston_controller.extendPiston2();
//         Serial.println("Piston 2 activated");
//         goto state_check_LED_YELLOW; 
//     } 
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa activare piston "Abreinigung"                  -->     Verificare culoare galbena LED                      (SENZOR CULOARE)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_check_LED_YELLOW:
//     {
//         unsigned long time_of_checking_led_yellow = millis();
//         const int stop_searching_led_yellow = 10000;  // 10 secunde
//         bool error_searching_led_YELLOW = false;
//         while(true)
//         {
//             int red_value2 = colorDetector.detectRed();
//             int green_value2 = colorDetector.detectGreen();
//             int blue_value2 = colorDetector.detectBlue();
//             Serial.println("Red = " + String(red_value2) + "  Green = " + String(green_value2) + "  Blue = " + String(blue_value2));
//             if(red_value2 > green_value2 && red_value2 > blue_value2)   // TODO: Calibrate and change to 0-255
//             {
//                 Serial.println("RED LED ON");
//             }
//             else if (red_value2 > blue_value2 && green_value2 > blue_value2)
//             {
//                 Serial.println("YELLOW LED ON");
//                 goto state_deactivate_piston2;
//             }
//             else
//             {
//                 Serial.println("Unknown color");
//             }

//             if (millis() - time_of_checking_led_yellow >= stop_searching_led_yellow) 
//             {
//                 Serial.println("Timeout: " + String(stop_searching_led_yellow/1000) + " seconds have elapsed since started checking if LED is YELLOW");
//                 error_searching_led_YELLOW = true;
//                 piston_controller.retractPiston2();
//                 Serial.println("Piston 2 deactivated");            
//                 break;
//             }
//         }

//         while(error_searching_led_YELLOW == true)
//         {
//             Serial.println("YELLOW LED not detected. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
//             analogWrite(PIN_Buzzer, 255);
//             analogWrite(PIN_LED_Red, 255);
//             analogWrite(PIN_Button_Fail_LED, 255);
//             if(digitalRead(PIN_Button_Fail_Switch) == HIGH)
//             {
//                 Serial.println("Fail confirmed");
//                 goto state_boardpower_deactivate;
//             }         
//         }
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare culoare galbena LED                 -->     Dezactivare piston "Abreinigung"                    (PISTON 2)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_deactivate_piston2:
//     {
//         piston_controller.retractPiston2();
//         Serial.println("Piston 2 deactivated");
//         goto state_check_synchronmotor; 
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa dezactivare piston "Abreinigung"               -->     Verificare rotire synchronmotor                      (SENZOR OPTIC)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_check_synchronmotor:
//     {
//         Serial.println("Beginning counting synchronmotor rotations");
//         bool error_checking_optical_rotation = false;
//         bool checking_optical_rotation = opticalCounter.countButtonPresses(Button_Count_Limit_Presses, Button_Count_Limit_Time);
//         if (checking_optical_rotation == true) 
//         {
//             Serial.println("Synchronmotor successfully rotated!");
//             goto state_activate_piston3;
//         }
//         else
//         {
//             Serial.println("Error. Time expired. Button not pressed successfully");
//             error_checking_optical_rotation == true;
//         }

//         while(error_checking_optical_rotation == true)
//         {
//             Serial.println("Synchronmotor NOT rotating. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
//             analogWrite(PIN_Buzzer, 255);
//             analogWrite(PIN_LED_Red, 255);
//             analogWrite(PIN_Button_Fail_LED, 255);
//             if(digitalRead(PIN_Button_Fail_Switch) == HIGH)
//             {
//                 Serial.println("Fail confirmed");
//                 goto state_boardpower_deactivate;
//             }         
//         }
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare "Synchronmotor"                     -->     Activare piston stampila PASS                       (PISTON 3)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_activate_piston3:
//     {
//         piston_controller.extendPiston3();
//         Serial.println("Piston 3 activated");
//         goto state_confirm_pass;
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa activare stampila PASS                         -->     Aprindere LED verde                                 (LED VERDE)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_confirm_pass:
//     {
//         analogWrite(PIN_LED_Green, 255);
//         Serial.println("Potentiometer centered. Green LED ON");
//         goto state_deactivate_piston3;
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa aprindere LED verde                            -->     Dezactivare piston stampila PASS                    (PISTON 3)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_deactivate_piston3:
//     {
//         piston_controller.retractPiston3();
//         Serial.println("Piston 3 deactivated");
//         goto state_boardpower_deactivate;
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa dezactivare piston stampila validare           -->     Comutare releu "Boardpower" in OFF                  (PISTON 3)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_boardpower_deactivate:
//     {
//         analogWrite(PIN_Buzzer, 0);
//         analogWrite(PIN_LED_Red, 0);
//         analogWrite(PIN_Button_Fail_LED, 0);
//         analogWrite(PIN_Relay, LOW);
//         Serial.println("Boardpower deactivated");
//         // goto state_check_door_closed;

//         int door_final_state = digitalRead(PIN_Door);
//         Serial.println("Final door state is: "+ String(door_final_state));
//         Serial.println("Checking if door is closed");
//         while(door_final_state == HIGH)
//         {
//             Serial.println("Door is closed. OPEN THE DOOR");
//             int door_final_state_check = digitalRead(PIN_Door);
//             if(door_final_state_check == LOW)
//             {
//                 Serial.println("Door is open. PROCCESS COMPLETE");
//                 goto state_check_door_closed;
//             }
//         }
//     }
// }