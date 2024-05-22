#include <Arduino.h>
#include "DisplayController.h"
#include "ButtonCounter.h"
#include "PistonController.h"
#include <WiFi.h>
#include <HTTPClient.h>

#define PIN_Piston1             17      // Brown
#define PIN_Piston2             16      // Red
#define PIN_Piston3             18       // Orange               CHANGE BECAUSE WiFi Connection
#define PIN_Relay               19//                            CHANGE WiFi
#define PIN_Door                33//                            CHANGE WiFi
#define PIN_Button_Fail_LED     32      // Same
#define PIN_Button_Fail_Switch  2        //                     CHANGE WiFI
#define PIN_Buzzer              23      // Modify if annoying
#define PIN_LED_Red             32      //                      CHANGE WiFi
#define PIN_LED_Green           5
//#define intled                  4

#define Display_Columns                 16
#define Display_Rows                    2
#define Display_Address                 0x27
#define Button_Count_Limit_Presses      10

//const char* ssid = "EDW_CX_AP";
//const char* password = "89089455";
// const char* calibrate =         "http://192.168.4.1/calibrate";
// const char* checkRedLed =       "http://192.168.4.1/redled";
// const char* minimumVoltage =    "http://192.168.4.1/minimumvoltage";
// const char* maximumVoltage =    "http://192.168.4.1/maximumvoltage";
// const char* chkYellowLED =      "http://192.168.4.1/yellowled";
// const char* checkSynchromotor = "http://192.168.4.1/synchromotor";
volatile int initialized = 0;
const char* fail = "FAIL";
const char* pass = "PASS";

// String calibresult = "";
// String redLEDresult = "";
// String minVoltresult = "";
// String maxVoltresult = "";
// String yellowLEDresult = "";
// String syncroResult = "";

PistonController piston_controller(PIN_Piston1, PIN_Piston2, PIN_Piston3);
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
    //pinMode(intled, OUTPUT);

    analogWrite(PIN_Relay, 0);
    analogWrite(PIN_Button_Fail_LED, 0);
    analogWrite(PIN_Buzzer, 0);
    analogWrite(PIN_LED_Red, 0);
    analogWrite(PIN_LED_Green, 0);
    piston_controller.retractPiston1();
    piston_controller.retractPiston2();
    piston_controller.retractPiston3();
    

}
String httpExecute(const char* function) 
{
  HTTPClient http;
  http.begin(function);
  int httpReturn = http.GET();
  
  String payload = "--"; 
  
  if (httpReturn > 0) 
  {
    Serial.print("HTTP Response code: ");
    Serial.println(payload);
    payload = http.getString();
  }
//   else 
//   {
//     Serial.print("Error code: ");
//     Serial.println(httpReturn);
//   }

  http.end();
  return payload;
}
void loop()
{
    if (initialized == 0){
    //volatile int il = 1;
    WiFi.begin("EDW_CX_AP", "89089455");
        Serial.print("Se conecteaza...");
        displayLCD.printSecondRow("Se conecteaza.");
        while(WiFi.status() !=WL_CONNECTED);
        {
            //il++;
            //Serial.print(".");
            displayLCD.printFirstRow("Astept...");
            //analogWrite(intled, il);
            delay(500);
            if(il == 255){il=1;}
        }
    //il = 0;
    //analogWrite(intled, il);
    initialized++;
    goto state_check_door_open;
    }
    else{goto state_check_door_closed;}


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
        displayLCD.printFirstRow("CENTRARE AX POT");
        String calibresult = httpExecute("http://192.168.4.1/calibrate");
        Serial.print("Rezultat centrare ax pote.");
        Serial.println(calibresult);
        const char* value = calibresult.c_str();
        bool ismatch = (strcmp(value, pass)==0);
        if(ismatch == true)
        {
            displayLCD.printSecondRowNoClear("AX CENTRAT");
            goto state_check_door_closed;
        }
        else
        {
            displayLCD.printSecondRowNoClear("EROARE!");
            goto state_check_door_open;
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
        while(door_closed_state == HIGH) 
        {
            Serial.println("Door is open");
            displayLCD.printBothRows("INCHIDETI CLAPA!", "INCEPE TESTAREA");
            int door_closed_state_check = digitalRead(PIN_Door);
            if(door_closed_state_check == LOW)     
            {
                Serial.println("Door is closed");
                analogWrite(PIN_LED_Green, 0);
                goto state_activate_piston1;
            }
        }
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare usa inchisa                         -->     Activare piston "Pruftaste"                         (PISTON 1)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_activate_piston1:
    {
        piston_controller.extendPiston1();
        delay(400);
        displayLCD.printFirstRow("TESTARE...");
        Serial.println("Piston 1 activated");
        goto state_boardpower_activate;
    }    
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa activare piston "Pruftaste"                    -->     Comutare releu "Boardpower"                         (RELEU BOARDPOWER)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_boardpower_activate:
    {
        analogWrite(PIN_Relay, 255);
        displayLCD.printSecondRowNoClear("ALIMENTARE UNITATE!");
        delay(1300);
        Serial.println("Boardpower activated");
        goto state_check_LED_RED;
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa comutare releu "Boardpower"                    -->     Verificare culoare rosie LED                        (SENZOR CULOARE)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_check_LED_RED:
    {
        bool error_searching_led_RED = false;
        displayLCD.printSecondRowNoClear("TESTARE LED ROSU");
        String redLEDresult = httpExecute("http://192.168.4.1/redled");
        Serial.print("Rezultat verificare LED Rosu:");
        Serial.println(redLEDresult);
        bool ismatch = (redLEDresult == pass);
        if(ismatch == true)
        {
            displayLCD.printSecondRowNoClear("LED ROSU OK");
            goto state_deactivate_piston1;
        } 
        else if(redLEDresult == fail)
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
            if(digitalRead(PIN_Button_Fail_Switch) == LOW)
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
        Serial.println("Piston 1 deactivated");
        goto state_voltage_check_min;
    }     
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa dezactivare piston "Pruftaste"                 -->     Rotire stepper in pozitia MIN                       (STEPPER)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa rotire stepper la MIN                          -->     Verificare senzor tensiune MIN                      (ZMPT101B)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_voltage_check_min:
    {
        bool error_checking_voltage_MIN = false;
        Serial.println("Average of last voltage values: ");
        displayLCD.printSecondRowNoClear("TESTARE VAL. MIN");
        String minVoltresult = httpExecute("http://192.168.4.1/minimumvoltage");
        Serial.print("Rezultat masuratoare tensiune minima:");
        Serial.println(minVoltresult);
        const char* value = minVoltresult.c_str();
        Serial.print("value:");
        Serial.println(value);

        int blablav = strcmp(value,pass);
        Serial.print("Blablav: ");
        Serial.println(blablav);
        bool ismatch = 0;

        if(blablav == 0)
        {
            Serial.print("Blablav ESTE 0; String-uri la fel");
            ismatch = 1;           
        }
        else if(blablav != 0)
        {
            Serial.print("Blablav NU ESTE 0; String-uri DIFERITE");
            Serial.print("Blablav gresit: ");
            Serial.println(blablav);
            ismatch = 0;            
        }

        // bool ismatch = (strcmp(value, pass)==0);
        Serial.println(ismatch);
        if(ismatch == 1)
        {
            displayLCD.printSecondRowNoClear("VALOARE MIN OK");
            goto state_voltage_check_MAX;
        }
        else if(ismatch == 0)
        {
            error_checking_voltage_MIN == true;
        }
        while(error_checking_voltage_MIN == true)
        {
            Serial.println("MIN voltage value NOT OK. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
            displayLCD.printBothRows("CONFIRMATI FAIL","VALOARE MIN NOK");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
            analogWrite(PIN_Button_Fail_LED, 255);
            if(digitalRead(PIN_Button_Fail_Switch) == LOW)
            {
                Serial.println("Fail confirmed");
                goto state_boardpower_deactivate;
            }         
        }
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare valoare MIN                         -->     Rotire stepper in pozitia MAX                       (STEPPER)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa rotire stepper la MAX                          -->     Verificare senzor tensiune MAX                      (ZMPT101B)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_voltage_check_MAX:
    {
        bool error_checking_voltage_MAX = false;
        displayLCD.printSecondRowNoClear("TESTARE VAL MAX");
        String maxVoltresult = httpExecute("http://192.168.4.1/maximumvoltage");
        Serial.print("Rezultat masuratoare tensiune maxima:");
        Serial.println(maxVoltresult);
        bool ismatch = (maxVoltresult == pass);
        if(ismatch == true)
        {
            displayLCD.printSecondRowNoClear("VALOARE MAX OK");
            goto state_activate_piston2;
        }
        else if(maxVoltresult == "FAIL")
        {
            error_checking_voltage_MAX == true;
        }
        while(error_checking_voltage_MAX == true)
        {
            displayLCD.printBothRows("CONFIRMATI FAIL","VALOARE MAX NOK");
            Serial.println("MAX voltage value NOT OK. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
            analogWrite(PIN_Button_Fail_LED, 255);
            if(digitalRead(PIN_Button_Fail_Switch) == LOW)
            {
                Serial.println("Fail confirmed");
                goto state_boardpower_deactivate;
            }         
        }
    }
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa verificare valoare MAX                         -->     Centrare stepper                                    (STEPPER)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa centrare stepper                               -->     Activare piston "Abreinigung"                       (PISTON 2)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_activate_piston2:
    {
        piston_controller.extendPiston2();
        delay(200);
        displayLCD.printFirstRow("Piston 2 ON");
        Serial.println("Piston 2 activated");
        goto state_check_LED_YELLOW;
        
    } 
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ////    Dupa activare piston "Abreinigung"                  -->     Verificare culoare galbena LED                      (SENZOR CULOARE)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state_check_LED_YELLOW:
    {
        unsigned long time_of_checking_led_yellow = millis();
        bool error_searching_led_YELLOW = false;
        displayLCD.printSecondRowNoClear("TESTARE LED GALB");
        String yellowLEDresult = httpExecute("http://192.168.4.1/yellowled");
        Serial.print("Rezultat verificare LED Galben:");
        Serial.println(yellowLEDresult);
        bool ismatch = (yellowLEDresult == pass);
        if(ismatch == true)
        {
            displayLCD.printSecondRowNoClear("LED GALBEN OK");
            goto state_deactivate_piston2;
        }
        else if(yellowLEDresult == "FAIL")
        {
            error_searching_led_YELLOW == true;
        }
        while(error_searching_led_YELLOW == true)
        {
            Serial.println("YELLOW LED not detected. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
            displayLCD.printBothRows("CONFIRMATI FAIL","LED GALBEN NOK");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
            analogWrite(PIN_Button_Fail_LED, 255);
            if(digitalRead(PIN_Button_Fail_Switch) == LOW)
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
        delay(500);
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
        displayLCD.printSecondRowNoClear("TESTARE S-MOTOR");
        String syncroResult = httpExecute("http://192.168.4.1/synchromotor");
        Serial.print("Rezultat verificare synchromotor:");
        Serial.println(syncroResult);
        bool ismatch = (syncroResult == "PASS");
        if(ismatch == true)
        {
            displayLCD.printSecondRowNoClear("SYNCHROMOTOR OK!");
            goto state_activate_piston3;
        }
        else if(syncroResult == "FAIL")
        {
            error_checking_optical_rotation == true;
        }
        while(error_checking_optical_rotation == true)
        {
            Serial.println("Synchronmotor NOT rotating. PRESS CONFIRM FAIL & OPEN THE DOOR !!!");
            displayLCD.printBothRows("CONFIRMATI FAIL","SYNCHROMOTOR NOK");
            analogWrite(PIN_Buzzer, 255);
            analogWrite(PIN_LED_Red, 255);
            analogWrite(PIN_Button_Fail_LED, 255);
            if(digitalRead(PIN_Button_Fail_Switch) == LOW)
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

        int door_final_state = digitalRead(PIN_Door);
        Serial.println("Final door state is: "+ String(door_final_state));
        Serial.println("Checking if door is closed");
        while(door_final_state == LOW)
        {
            Serial.println("Door is closed. OPEN THE DOOR");
            int door_final_state_check = digitalRead(PIN_Door);
            if(door_final_state_check == HIGH)
            {
                Serial.println("Door is open. PROCCESS COMPLETE");
                goto state_check_door_closed;
            }
        }
    }
}


