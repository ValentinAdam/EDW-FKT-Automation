#include <Arduino.h>
#include "DisplayController.h"
#include "ButtonCounter.h"
#include "PistonController.h"
#include "Communication.h"
#include <driver/dac.h>
#include <driver/adc.h>

#define ADC_PIN                 34
#define PIN_DAC                 25
#define PIN_Piston1             17      // Brown
#define PIN_Piston2             16      // Red
#define PIN_Piston3             4       // Orange
#define PIN_Relay               27
#define PIN_Door                14
#define PIN_Button_Fail_LED     33      // Same
#define PIN_Button_Fail_Switch  13
#define PIN_Buzzer              23      // Modify if annoying
#define PIN_LED_Red             12      // Same
#define PIN_LED_Green           5
#define PIN_Microswitch         18

#define Display_Columns                 16
#define Display_Rows                    2
#define Display_Address                 0x27
#define Button_Count_Limit_Presses      10

volatile int returned = 0;
PistonController piston_controller(PIN_Piston1, PIN_Piston2, PIN_Piston3);
DisplayController displayLCD(Display_Columns, Display_Rows, Display_Address);
Communication communication;

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

    delay(1500);//asteptam SLAVE-ul sa interogheze adc-ul
    communication.dac_tx_sync();
    while(returned != 50)//asteptam raspunsul de la SLAVE
    {   
        returned = communication.adc_rx();
        delay(50);
        displayLCD.printFirstRow("CONECTARE SLAVE");
    }
    displayLCD.printFirstRow("SLAVE CONECTAT");
    delay(800);
    returned = 0;
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
            displayLCD.printFirstRow("RIDICATI CLAPA");
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
        communication.dac_tx_potCalib();
        delay(300);
        while(returned == 0)
        {
            returned = communication.adc_rx();
            delay(5);
        }
        if(returned == 20)
        {
            returned = 0;
            goto state_check_door_open;
        }
        else if(returned == 15)
        {
            //display pass, goto next
            returned = 0;
            goto state_check_door_closed;

        }
        
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa atingere pozitie de "0"                        -->     Centrare potentiometru                              (STEPPER MOTOR)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa centrare potentiometru                         -->     Activare LED verde confirmare initializare          (LED VERDE)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa confirmare initializare cu succes              -->     Verificare senzor usa inchisa                       (SENZOR USA)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_check_door_closed:
    {
        int door_closed_state = digitalRead(PIN_Door);
        Serial.println("Door state is: " + String(door_closed_state));
        Serial.println("Checking if door is closed");
        unsigned long time_of_checking_door_closed = millis();
        const int stop_searching_door_closed = 50000;  // 10 secunde
        bool error_searching_door_closed = false;
        while(door_closed_state == HIGH) 
        {
            Serial.println("Door is open");
            displayLCD.printSecondRowNoClear("INCHIDETI CLAPA");
            int door_closed_state_check = digitalRead(PIN_Door);
            if(door_closed_state_check == LOW)     
            {
                Serial.println("Door is closed");
                delay(700);
                analogWrite(PIN_LED_Green, 0);
                goto state_activate_piston1;
            }
            if (millis() - time_of_checking_door_closed >= stop_searching_door_closed) 
            {
                Serial.println("Timeout: " + String(stop_searching_door_closed/1000) + " seconds have elapsed since started checking if door is closed");
                error_searching_door_closed = true;
                break;
            }
        }
        while(error_searching_door_closed == true)
        {
            Serial.println("Door not closed. PRESS CONFIRM FAIL & CLOSE THE DOOR !!!");
            displayLCD.printBothRows("Confirm FAIL","Door not closed");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
            analogWrite(PIN_Button_Fail_LED, 255);
            if(digitalRead(PIN_Button_Fail_Switch) == HIGH)
            {
                Serial.println("Fail confirmed");
                goto state_check_door_closed;
            }         
        }
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare usa inchisa                         -->     Activare piston "Pruftaste"                         (PISTON 1)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_activate_piston1:
    {
        piston_controller.extendPiston1();
        delay(500);
        displayLCD.printFirstRow("Pruftaste active");
        Serial.println("Piston 1 activated");
        goto state_boardpower_activate;
    }    
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa activare piston "Pruftaste"                    -->     Comutare releu "Boardpower"                         (RELEU BOARDPOWER)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_boardpower_activate:
    {
        analogWrite(PIN_Relay, 255);
        delay(2000);
        displayLCD.printSecondRowNoClear("Boardpower ON");
        Serial.println("Boardpower activated");
        goto state_check_LED_RED;
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa comutare releu "Boardpower"                    -->     Verificare culoare rosie LED                        (SENZOR CULOARE)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_check_LED_RED:
    {
        bool error_searching_led_RED = false;
        displayLCD.printFirstRow("Checking RED LED");
        communication.dac_tx_checkRedLED();
        while(returned == 0)
        {
            returned = communication.adc_rx();
            delay(5);
        }
        if(returned == 30)
        {
            goto state_deactivate_piston1;
        } 
        else if(returned == 35)
        {
            error_searching_led_RED = true;
        }
        while(error_searching_led_RED == true)
        {
            Serial.println("RED LED not detected. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
            displayLCD.printBothRows("CONFIRMATI FAIL!","LED ROSU NOK");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
            analogWrite(PIN_Button_Fail_LED, 255);
            if(digitalRead(PIN_Button_Fail_Switch) == HIGH)
            {
                Serial.println("Fail confirmed");
                goto state_boardpower_deactivate;
            }         
        }
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare LED rosu                            -->     Dezactivare piston "Pruftaste"                      (PISTON 1)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_deactivate_piston1:
    {
        piston_controller.retractPiston1();
        displayLCD.printFirstRow("Piston 1 OFF");
        Serial.println("Piston 1 deactivated");
        goto state_voltage_check_min;
    }     
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa dezactivare piston "Pruftaste"                 -->     Rotire stepper in pozitia MIN                       (STEPPER)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_stepper_to_min:
//     {
//         displayLCD.printBothRows("Stepper to MIN","<-------------");
//         Serial.println("Moving stepper to MIN voltage position...");
//         myStepper.step(stepsCenterToLeft);
//         Serial.println("Stepper reached MIN voltage position...");
//         displayLCD.printBothRows("Stepper reached","MIN position");
//         delay(1500);
//         goto state_voltage_check_MIN;
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa rotire stepper la MIN                          -->     Verificare senzor tensiune MIN                      (ZMPT101B)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_voltage_check_min:
    {
        bool error_checking_voltage_MIN = false;
        //float voltage_value_MIN = voltage_monitor.measureVoltage(Voltage_Measurements, Voltage_Samples);
        Serial.println("Average of last voltage values: ");
        displayLCD.printFirstRow("TESTARE VAL. MIN");
        // if(voltage_value_MIN > 94 && voltage_value_MIN < 108)
        communication.dac_tx_checkMinVoltage();
        while(returned == 0)
        {
            returned = communication.adc_rx();
            delay(5);
        }
        if (returned == 45)
        {
            returned = 0;
            displayLCD.printSecondRowNoClear("VALOARE MIN OK");
            goto state_voltage_check_MAX;
        }
        else if(returned == 50)
        {
            returned = 0;
            error_checking_voltage_MIN == true;
        }
        while(error_checking_voltage_MIN == true)
        {
            Serial.println("MIN voltage value NOT OK. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
            displayLCD.printBothRows("CONFIRMATI FAIL","TENSIUNE MIN NOK");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
            analogWrite(PIN_Button_Fail_LED, 255);
            if(digitalRead(PIN_Button_Fail_Switch) == HIGH)
            {
                Serial.println("Fail confirmed");
                goto state_boardpower_deactivate;
            }         
        }
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare valoare MIN                         -->     Rotire stepper in pozitia MAX                       (STEPPER)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_stepper_to_max:
//     {
//         displayLCD.printBothRows("Stepper to MAX","------------->");
//         Serial.println("Moving stepper to MAX voltage position...");
//         myStepper.step(stepsLeftToRight);
//         delay(2000);
//         displayLCD.printBothRows("Stepper reached","MAX position");
//         Serial.println("Stepper reached MAX voltage position...");
//         goto state_voltage_check_MAX;
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa rotire stepper la MAX                          -->     Verificare senzor tensiune MAX                      (ZMPT101B)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_voltage_check_MAX:
    {
        bool error_checking_voltage_MAX = false;
        //float voltage_value_MAX = voltage_monitor.measureVoltage(Voltage_Measurements, Voltage_Samples);
        //Serial.println("Average of last voltage values: " + String(voltage_value_MAX));
        displayLCD.printFirstRow("TESTARE VAL MAX");
        communication.dac_tx_checkMaxVoltage();
        while(returned == 0)
        {
            returned = communication.adc_rx();
            delay(5);
        }
        if (returned == 60)
        {
            returned = 0;
            displayLCD.printSecondRowNoClear("VALOARE MAX OK");
            goto state_activate_piston2;
        }
        else if(returned == 65)
        {
            returned = 0;
            error_checking_voltage_MAX == true;
        }
        while(error_checking_voltage_MAX == true)
        {
            displayLCD.printBothRows("CONFIRMATI FAIL","TENSIUNE MAX NOK");
            Serial.println("MAX voltage value NOT OK. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
            analogWrite(PIN_Button_Fail_LED, 255);
            if(digitalRead(PIN_Button_Fail_Switch) == HIGH)
            {
                Serial.println("Fail confirmed");
                goto state_boardpower_deactivate;
            }         
        }
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare valoare MAX                         -->     Centrare stepper                                    (STEPPER)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     state_stepper_to_center:
//     {
//         displayLCD.printBothRows("Stepper center","<------------>");
//         Serial.println("Moving stepper to CENTER position...");
//         myStepper.step(stepsRightToCenter);
//         delay(1500);
//         displayLCD.printBothRows("Stepper reached","Central position");
//         Serial.println("Stepper reached CENTER position...");
//         goto state_activate_piston2;
//     }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa centrare stepper                               -->     Activare piston "Abreinigung"                       (PISTON 2)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_activate_piston2:
    {
        piston_controller.extendPiston2();
        displayLCD.printFirstRow("Piston 2 ON");
        Serial.println("Piston 2 activated");
        displayLCD.printFirstRow("TESTARE LED GALB");
        communication.dac_tx_checkYellowLED();
        
    } 
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa activare piston "Abreinigung"                  -->     Verificare culoare galbena LED                      (SENZOR CULOARE)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_check_LED_YELLOW:
    {
        unsigned long time_of_checking_led_yellow = millis();
        //const int stop_searching_led_yellow = 10000;  // 10 secunde
        bool error_searching_led_YELLOW = false;
        displayLCD.printFirstRow("TESTARE LED GALB");
        communication.dac_tx_checkYellowLED();
        while(returned == 0)
        {
            returned = communication.adc_rx();
            delay(5);
        }
        if (returned == 60)
        {
            returned = 0;
            displayLCD.printSecondRowNoClear("VALOARE MAX OK");
            goto state_deactivate_piston2;
        }
        else if(returned == 65)
        {
            returned = 0;
            error_searching_led_YELLOW == true;
        }
        while(error_searching_led_YELLOW == true)
        {
            Serial.println("YELLOW LED not detected. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
            displayLCD.printBothRows("Confirm FAIL","YELLOW LED NOK");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
            analogWrite(PIN_Button_Fail_LED, 255);
            if(digitalRead(PIN_Button_Fail_Switch) == HIGH)
            {
                Serial.println("Fail confirmed");
                goto state_boardpower_deactivate;
            }
        }
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare culoare galbena LED                 -->     Dezactivare piston "Abreinigung"                    (PISTON 2)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_deactivate_piston2:
    {
        piston_controller.retractPiston2();
        displayLCD.printFirstRow("Piston 2 OFF");
        Serial.println("Piston 2 deactivated");
        goto state_check_synchronmotor; 
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa dezactivare piston "Abreinigung"               -->     Verificare rotire synchronmotor                      (SENZOR OPTIC)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_check_synchronmotor:
    {
        Serial.println("Beginning counting synchronmotor rotations");
        bool error_checking_optical_rotation = false;
        displayLCD.printBothRows("Checking", "synchronmotor");
        communication.dac_tx_checkSincromotor();
        while(returned == 0)
        {
            returned = communication.adc_rx();
            delay(5);
        }
        if (returned == 90)
        {
            returned = 0;
            displayLCD.printSecondRowNoClear("VALOARE MAX OK");
            goto state_deactivate_piston2;
        }
        else if(returned == 95)
        {
            returned = 0;
            error_checking_optical_rotation == true;
        }
        while(error_checking_optical_rotation == true)
        {
            Serial.println("Synchronmotor NOT rotating. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
            displayLCD.printBothRows("Confirm FAIL","Synchronmotor");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
            analogWrite(PIN_Button_Fail_LED, 255);
            if(digitalRead(PIN_Button_Fail_Switch) == HIGH)
            {
                Serial.println("Fail confirmed");
                goto state_boardpower_deactivate;
            }         
        }
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare "Synchronmotor"                     -->     Activare piston stampila PASS                       (PISTON 3)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_activate_piston3:
    {
        piston_controller.extendPiston3();
        displayLCD.printPASS();
        Serial.println("Piston 3 activated");
        goto state_confirm_pass;
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa activare stampila PASS                         -->     Aprindere LED verde                                 (LED VERDE)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_confirm_pass:
    {
        analogWrite(PIN_LED_Green, 255);
        Serial.println("UNIT PASS. Green LED ON");
        goto state_deactivate_piston3;
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa aprindere LED verde                            -->     Dezactivare piston stampila PASS                    (PISTON 3)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_deactivate_piston3:
    {
        piston_controller.retractPiston3();
        Serial.println("Piston 3 deactivated");
        goto state_boardpower_deactivate;
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa dezactivare piston stampila validare           -->     Comutare releu "Boardpower" in OFF                  (PISTON 3)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_boardpower_deactivate:
    {
        analogWrite(PIN_Buzzer, 0);
        analogWrite(PIN_LED_Red, 0);
        analogWrite(PIN_Button_Fail_LED, 0);
        analogWrite(PIN_Relay, LOW);
        Serial.println("Boardpower deactivated");
        // goto state_check_door_closed;

        int door_final_state = digitalRead(PIN_Door);
        Serial.println("Final door state is: "+ String(door_final_state));
        Serial.println("Checking if door is closed");
        while(door_final_state == HIGH)
        {
            Serial.println("Door is closed. OPEN THE DOOR");
            int door_final_state_check = digitalRead(PIN_Door);
            if(door_final_state_check == LOW)
            {
                Serial.println("Door is open. PROCCESS COMPLETE");
                goto state_check_door_closed;
            }
        }
    }







}