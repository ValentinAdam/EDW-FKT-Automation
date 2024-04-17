#include <Arduino.h>
#include "ColorDetector.h"
#include "ButtonCounter.h"
#include "VoltageSensor.h"
#include "Stepper.h"


#define PIN_Stepper1            32
#define PIN_Stepper2            33
#define PIN_Stepper3            25
#define PIN_Stepper4            26
#define PIN_Color_S0            21
#define PIN_Color_S1            22
#define PIN_Color_S2            2
#define PIN_Color_S3            15
#define PIN_Color_Out           39
#define PIN_Voltmeter           36
#define PIN_Optical_Count       19
#define PIN_Microswitch         18

#define Button_Count_Limit_Presses      10
#define Button_Count_Limit_Time         30000
#define Voltage_Calibration             84
#define Voltage_Phase_Shift             1.7
#define Voltage_Measurements            80
#define Voltage_Samples                 20


// const double stepsPerRevolution = 2037.8864;                //    number of steps per revolution = 2037.8864    //  2048
// const double degreePerStep      = stepsPerRevolution/360;   //    celsius degree per step
// const double stepsLeftToRight   = 240*degreePerStep;        //    steps for 240 celsius degree
// const double stepsCenterToLeft  = -120*degreePerStep;       //    steps for 120 celsius degree
// const double stepsRightToCenter = -120*degreePerStep;       //    negative steps for 120 celsius degree

const double stepsPerRevolution = 200;                //    number of steps per revolution = 2037.8864    //  2048
const double degreePerStep      = stepsPerRevolution/360;   //    celsius degree per step
const double stepsLeftToRight   = -240*degreePerStep;        //    steps for 240 celsius degree
const double stepsCenterToLeft  = 120*degreePerStep;       //    steps for 120 celsius degree
const double stepsRightToCenter = 120*degreePerStep;       //    negative steps for 120 celsius degree

Stepper myStepper(stepsPerRevolution, PIN_Stepper1, PIN_Stepper2, PIN_Stepper3, PIN_Stepper4);
ColorDetector colorDetector(PIN_Color_S0, PIN_Color_S1, PIN_Color_S2, PIN_Color_S3, PIN_Color_Out);
VoltageSensor voltage_monitor(PIN_Voltmeter, Voltage_Calibration, Voltage_Phase_Shift);
ButtonCounter opticalCounter(PIN_Optical_Count);


void setup()
{
    Serial.begin(115200);
    myStepper.setSpeed(60);   //  stepper speed in rpm
    colorDetector.initialize();
    opticalCounter.initialize();
    pinMode(PIN_Microswitch, INPUT_PULLUP);
    
}











void loop()
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Dupa verificare senzor usa deschisa                 -->     Rotire potentiometru spre "0"                       (STEPPER MOTOR)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    In timpul rotirii potentiometrului                  -->     Verificare pozitie de "0"                           (MICROSWITCH)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_search_zero:
    {
        Serial.println("Beginning searching the zero point");
        int microswitch_state = digitalRead(PIN_Microswitch);
        Serial.println("Microswitch state is: " + String(microswitch_state));
        unsigned long time_of_searching_zero = millis();
        const int stop_searching_zero = 10000;  // 10 secunde
        bool error_searching_zero = false;
        while(microswitch_state == HIGH)
        {
            Serial.println("Microswitch not pressed");
            // myStepper.step(25);
            myStepper.step(-10);
            Serial.println("Stepper motor moved 1 step to the right");
            displayLCD.printBothRows("CALIBRATING", "---------->");
            int microswitch_state_check = digitalRead(PIN_Microswitch);
            if(microswitch_state_check == LOW)
            {
                Serial.println("Microswitch is pressed");
                goto state_center_potentiometer;
            }
            if (millis() - time_of_searching_zero >= stop_searching_zero)
            {
                Serial.println("Timeout: " + String(stop_searching_zero/1000) + " seconds have elapsed since started searching for zero point");
                error_searching_zero = true;
                break;
            }
        }
        while(error_searching_zero == true)
        {
            Serial.println("Microswitch not pressed. TURN MAIN POWER OFF !!!");
            displayLCD.printBothRows("PRESS BUTTON","MAIN POWER OFF");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
        }
    }




}