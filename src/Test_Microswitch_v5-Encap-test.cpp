#include <Arduino.h>
#include "ButtonCounter.h"

#define PIN_Button_Count 13
#define Button_Count_Limit_Presses 10
#define Button_Count_Limit_Time 30000

ButtonCounter myButtonCounter(PIN_Button_Count);

void setup() 
{
    Serial.begin(115200);
    pinMode(PIN_Button_Count, INPUT_PULLUP);
}

void loop() 
{
    start:
    Serial.println("START OF THE PROGRAM");
    delay(3000);
    goto counter;


    counter:
    Serial.println("Begining counting");
    bool button_counter_value = myButtonCounter.countButtonPresses(Button_Count_Limit_Presses, Button_Count_Limit_Time);
    if (button_counter_value == true) 
    {
        Serial.println("Button successfully pressed!");
        goto end;
    }
    else
    {
        Serial.println("Error. Time expired. Button not pressed successfully");
        goto start;
    }


    end:
    Serial.println("END OF THE PROGRAM");
    delay(3000);
}
