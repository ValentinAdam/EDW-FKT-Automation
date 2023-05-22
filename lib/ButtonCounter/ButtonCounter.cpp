#include "ButtonCounter.h"

ButtonCounter::ButtonCounter(int pin)
{
    _pin = pin;
}

void ButtonCounter::initialize()
{
    pinMode(_pin, INPUT_PULLUP);
}

bool ButtonCounter::countButtonPresses(int requiredPresses, unsigned long timeout) 
{
    int count = 0;
    unsigned long time_of_button_count = millis();

    while (true) 
    {
        int button_state = digitalRead(_pin);
        Serial.print("Button state == ");
        Serial.println(button_state);
        Serial.print("Counter increment is == ");
        Serial.println(count);

        if(button_state == HIGH) 
        {
            Serial.println("The button is not pressed"); 
        } 
        else if(button_state == LOW) 
        {
            Serial.println("The button is pressed");
            count++;
            if(count == requiredPresses) 
            {
                Serial.println("Button pressed required times!");
                return true;
            }
        }

        if (millis() - time_of_button_count >= timeout) 
        {
            Serial.println("Timeout: " + String(timeout/1000) + " seconds have elapsed since the button was last pressed.");
            break;
        }

        delay(100);
    }

    return false;
}
