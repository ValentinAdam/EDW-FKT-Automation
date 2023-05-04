#ifndef BUTTONCOUNTER_H
#define BUTTONCOUNTER_H

#include <Arduino.h>

class ButtonCounter 
{
    public:
        ButtonCounter(int pin);
        bool countButtonPresses(int requiredPresses, unsigned long timeout);
    private:
        int pin;
};

#endif
