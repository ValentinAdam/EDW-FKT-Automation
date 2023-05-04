#ifndef ZMPT101B_H
#define ZMPT101B_H

#include <Arduino.h>

class ZMPT101B 
{
    public:
        ZMPT101B(int PIN);
        double getVoltage();
    private:
        int _PIN;
};

#endif
