#include <Arduino.h>
#include <driver/adc.h>
#include <driver/dac.h>
#include "ColorDetector.h"
#include "ButtonCounter.h"
#include "VoltageSensor.h"
#include "Stepper.h"
#include "Communication.h"

#define DAC_PIN                 25
#define ADC_PIN                 34
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
#define Volt_Min_UE_ll          95
#define Volt_Min_UE_lh          107
#define Volt_Min_US_ll          49
#define Volt_Min_US_lh          59
#define Volt_Max_UE_ll          220
#define Volt_Max_UE_lh          232
#define Volt_Max_US_ll          112
#define Volt_Max_US_lh          122
#define PIN_RegionSel           13

#define Button_Count_Limit_Presses      10
#define Button_Count_Limit_Time         30000
#define Voltage_Calibration             84
#define Voltage_Phase_Shift             1.7
#define Voltage_Measurements            80
#define Voltage_Samples                 20
volatile int command = 0;
int min_ll = 0;
int min_lh = 0;
int max_ll = 0;
int max_lh = 0; 

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
Communication communication;

void setup()
{
    Serial.begin(115200);
    myStepper.setSpeed(60);   //  stepper speed in rpm
    colorDetector.initialize();
    opticalCounter.initialize();
    pinMode(PIN_Microswitch, INPUT_PULLUP);
    pinMode(PIN_RegionSel, INPUT_PULLUP);
    if(PIN_RegionSel == HIGH)//pentru unitatile cu destinatia UE pinul va ramane neconectat(cel mai intalnit)
    {
         min_ll = Volt_Min_UE_ll;
         min_lh = Volt_Min_UE_lh;
         max_ll = Volt_Max_UE_ll;
         max_lh = Volt_Max_UE_lh;
    }
    else
    {
         min_ll = Volt_Min_US_ll;
         min_lh = Volt_Min_US_lh;
         max_ll = Volt_Max_US_ll;
         max_lh = Volt_Max_US_lh;
    }
    while(command == 0 )
    {
        command = communication.adc_rx();//interogam adc-ul 
        delay(50);
    }
    communication.dac_tx_sync();
}



void loop()
{
    command = 0;
    while(command == 0)
    {
        command = communication.adc_rx();
    }
    switch (command)
    {
        case 10:
            pot_calib();
            break;
        case 25:
            check_red_led();
            break;
        case 40:
            check_min_volt();
            break;
        case 55:
            check_max_volt();
            break;
        case 70:
            check_yellow_led();
            break;
        case 85:
            check_syncromotor();
            break;

    }
    
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Dupa verificare senzor usa deschisa                 -->     Rotire potentiometru spre "0"                       (STEPPER MOTOR)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    In timpul rotirii potentiometrului                  -->     Verificare pozitie de "0"                           (MICROSWITCH)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pot_calib()
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
            //displayLCD.printBothRows("CALIBRATING", "---------->");
            int microswitch_state_check = digitalRead(PIN_Microswitch);
            if(microswitch_state_check == LOW)
            {
                Serial.println("Microswitch is pressed");
                delay(150);
                myStepper.step(stepsRightToCenter);
                communication.dac_tx_potCentered();
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
            communication.dac_tx_potCalibNOK();
        }
    }
void check_red_led()
{
    unsigned long time_of_checking_led_red = millis();
    const int stop_searching_led_red = 10000;  // 10 secunde
    bool error_searching_led_RED = false;
    //displayLCD.printFirstRow("Checking RED LED");
    while(true)
    {
        int red_value1 = colorDetector.detectRed();
        int green_value1 = colorDetector.detectGreen();
        int blue_value1 = colorDetector.detectBlue();
        Serial.println("Red = " + String(red_value1) + "  Green = " + String(green_value1) + "  Blue = " + String(blue_value1));
        //displayLCD.printSecondRowNoClear("R=" + String(red_value1) + "G=" + String(green_value1) + "B=" + String(blue_value1));
        if(red_value1 > green_value1 && red_value1 > blue_value1)   // TODO: Calibrate and change to 0-255
        {
            Serial.println("RED LED ON");
            communication.dac_tx_redLEDOK();
        }
        else if (red_value1 > blue_value1 && green_value1 > blue_value1)
        {
            Serial.println("YELLOW LED ON");
            communication.dac_tx_redLEDNOK();
        }
        if (millis() - time_of_checking_led_red >= stop_searching_led_red) 
        {
            Serial.println("Timeout: " + String(stop_searching_led_red/1000) + " seconds have elapsed since started checking if LED is RED");
            error_searching_led_RED = true;
            communication.dac_tx_redLEDNOK();
            Serial.println("Piston 1 deactivated");
            break;
        }
    }
}

    void check_min_volt()
    {
        myStepper.step(stepsCenterToLeft);
        delay(150);
        float voltage_value_MIN = voltage_monitor.measureVoltage(Voltage_Measurements, Voltage_Samples);
        if(voltage_value_MIN > min_ll && voltage_value_MIN < min_lh)
        {
            communication.dac_tx_minVoltageOK();
        }
        else
        {
            communication.dac_tx_minVoltageNOK();
        }
    }
    void check_max_volt()
    {
        myStepper.step(stepsLeftToRight);
        delay(150);
        float voltage_value_MAX = voltage_monitor.measureVoltage(Voltage_Measurements, Voltage_Samples);
        if(voltage_value_MAX > max_ll && voltage_value_MAX < max_lh)
        {
            communication.dac_tx_maxVoltageOK();
        }
        else
        {
            communication.dac_tx_maxVoltageNOK();
        }
    }
void check_yellow_led()
{
    myStepper.step(stepsRightToCenter);
    unsigned long time_of_checking_led_yellow = millis();
    const int stop_searching_led_yellow = 10000;  // 10 secunde
    bool error_searching_led_YELLOW = false;
    while(true)
    {
        int red_value2 = colorDetector.detectRed();
        int green_value2 = colorDetector.detectGreen();
        int blue_value2 = colorDetector.detectBlue();
        Serial.println("Red = " + String(red_value2) + "  Green = " + String(green_value2) + "  Blue = " + String(blue_value2));
        if(red_value2 > green_value2 && red_value2 > blue_value2)   // TODO: Calibrate and change to 0-255
        {
            Serial.println("RED LED ON");
            communication.dac_tx_yellowLEDNOK();
        }
        else if (red_value2 > blue_value2 && green_value2 > blue_value2)
        {
            Serial.println("YELLOW LED ON");
            communication.dac_tx_yellowLEDOK();
        }
        if (millis() - time_of_checking_led_yellow >= stop_searching_led_yellow) 
        {
            Serial.println("Timeout: " + String(stop_searching_led_yellow/1000) + " seconds have elapsed since started checking if LED is RED");
            error_searching_led_YELLOW = true;
            communication.dac_tx_redLEDNOK();
            Serial.println("Piston 1 deactivated");
            break;
        }
    }
}
void check_syncromotor()
{
    bool checking_optical_rotation = opticalCounter.countButtonPresses(Button_Count_Limit_Presses, Button_Count_Limit_Time);
        if (checking_optical_rotation == true) 
        {
            Serial.println("Synchronmotor successfully rotated!");
            goto state_activate_piston3;
        }
        else
        {
            Serial.println("Error. Time expired. Button not pressed successfully");
            error_checking_optical_rotation == true;
        }
}