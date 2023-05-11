#ifndef PistonController_H
#define PistonController_H

#include <Arduino.h>

class PistonController 
{
    public:
        PistonController(int pin1, int pin2, int pin3);
        void initialize();
        void extendPiston1();
        void retractPiston1();
        void extendPiston2();
        void retractPiston2();
        void extendPiston3();
        void retractPiston3();

    private:
        int _pin1;
        int _pin2;
        int _pin3;
};

#endif
