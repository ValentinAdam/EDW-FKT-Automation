#include <Arduino.h>
#include "DisplayController.h"
#include "ButtonCounter.h"
#include "PistonController.h"
#include <driver/dac.h>

#define PIN_DAC                 25
#define PIN_Piston1             17      // Brown
#define PIN_Piston2             16      // Red
#define PIN_Piston3             4       // Orange
#define PIN_Optical_Count       19
#define PIN_Relay               13
#define PIN_Door                14
#define PIN_Button_Fail_LED     33      // Same
#define PIN_Button_Fail_Switch  27
#define PIN_Buzzer              23      // Modify if annoying
#define PIN_LED_Red             12      // Same
#define PIN_LED_Green           5

#define Display_Columns                 16
#define Display_Rows                    2
#define Display_Address                 0x27
#define Button_Count_Limit_Presses      10
#define Button_Count_Limit_Time         30000

PistonController piston_controller(PIN_Piston1, PIN_Piston2, PIN_Piston3);
ButtonCounter opticalCounter(PIN_Optical_Count);
DisplayController displayLCD(Display_Columns, Display_Rows, Display_Address);


void setup()
{
    Serial.begin(115200);
    piston_controller.initialize();
    displayLCD.initialize();
    pinMode(PIN_Relay, OUTPUT);
    pinMode(PIN_Door, INPUT_PULLUP);
    pinMode(PIN_Button_Fail_Switch, INPUT_PULLUP);
    pinMode(PIN_Button_Fail_LED, OUTPUT);
    pinMode(PIN_Buzzer, OUTPUT);
    pinMode(PIN_LED_Red, OUTPUT);
    pinMode(PIN_LED_Green, OUTPUT);

    analogWrite(PIN_Relay, 0);
    analogWrite(PIN_Button_Fail_LED, 0);
    analogWrite(PIN_Buzzer, 0);
    analogWrite(PIN_LED_Red, 0);
    analogWrite(PIN_LED_Green, 0);
    piston_controller.retractPiston1();
    piston_controller.retractPiston2();
    piston_controller.retractPiston3();
    dac_output_enable(DAC_CHANNEL_1);

}

void loop()
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Pornire aparat (Se comuta buton "Main Power")       -->     Verificare senzor usa deschisa                      (BUTON USA)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_check_door_open:
    {
        int door_open_state = digitalRead(PIN_Door);
        Serial.println("Door state is: " + String(door_open_state));
        Serial.println("Checking if door is open");
        if(door_open_state == LOW)
        {
            Serial.println("Door is closed !!!");
            displayLCD.printFirstRow("OPEN THE DOOR");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
            goto state_check_door_open;
        }
        else
        {
            Serial.println("Door is open !!!");
            analogWrite(PIN_Buzzer, 0);
            analogWrite(PIN_LED_Red, 0);
            goto state_search_zero;
        }
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Dupa verificare senzor usa deschisa                 -->     Rotire potentiometru spre "0"                       (STEPPER MOTOR)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    In timpul rotirii potentiometrului                  -->     Verificare pozitie de "0"                           (MICROSWITCH)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_search_zero:
    {
        Serial.println("Beginning searching the zero point");
        Communication::dac_tx_potCalib();
        int result = 
        while(error_searching_zero == true)
        {
            Serial.println("Microswitch not pressed. TURN MAIN POWER OFF !!!");
            displayLCD.printBothRows("PRESS BUTTON","MAIN POWER OFF");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
        }
    }








}