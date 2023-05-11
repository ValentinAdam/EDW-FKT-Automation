#include <Arduino.h>
#include "PistonController.h"

PistonController::PistonController(int pin1, int pin2, int pin3) 
{
    _pin1 = pin1;
    _pin2 = pin2;
    _pin3 = pin3;
}

void PistonController::initialize() 
{
    pinMode(_pin1, OUTPUT);
    pinMode(_pin2, OUTPUT);
    pinMode(_pin3, OUTPUT);
}

void PistonController::extendPiston1() 
{
    digitalWrite(_pin1, HIGH);
    Serial.println("Piston 1 is HIGH");
}

void PistonController::retractPiston1() 
{
    digitalWrite(_pin1, LOW);
    Serial.println("Piston 1 is LOW");
}

void PistonController::extendPiston2() 
{
    digitalWrite(_pin2, HIGH);
    Serial.println("Piston 2 is HIGH");
}

void PistonController::retractPiston2() 
{
    digitalWrite(_pin2, LOW);
    Serial.println("Piston 2 is LOW");
}

void PistonController::extendPiston3() 
{
    digitalWrite(_pin3, HIGH);
    Serial.println("Piston 3 is HIGH");
}

void PistonController::retractPiston3() 
{
    digitalWrite(_pin3, LOW);
    Serial.println("Piston 3 is LOW");
}
