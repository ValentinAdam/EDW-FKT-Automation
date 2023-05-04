#include <Arduino.h>

#define PIN_Voltmeter 13

double ZMPT_Value = 0;
double ZMPT_Array[100];
double ZMPT_Max_Value = 0;
double ZMPT_MaxD = 0;
double ZMPT_VeffD = 0;
double ZMPT_Veff = 0;
double ZMPT_Veff_New = 0;

void setup() 
{
    Serial.begin(115200);
}

void loop() 
{
    for (int i = 0; i < 100; i++) 
    {
        ZMPT_Value = analogRead(PIN_Voltmeter);
        if (analogRead(PIN_Voltmeter) > 511) 
        {
            ZMPT_Array[i] = ZMPT_Value;
        }
        else 
        {
            ZMPT_Array[i] = 0;
        }
        delay(1);
    }

    ZMPT_Max_Value = 0;

    for (int i = 0; i < 100; i++)
    {
        if (ZMPT_Array[i] > ZMPT_Max_Value)
        {
            ZMPT_Max_Value = ZMPT_Array[i];
        }
    ZMPT_Array[i] = 0;
    }

    if (ZMPT_Max_Value != 0) 
    {
        ZMPT_MaxD = ZMPT_Max_Value;
        ZMPT_VeffD = ZMPT_MaxD / sqrt(2);
        ZMPT_Veff = (((ZMPT_VeffD - 420.76) / -90.24) * -210.2) + 210.2;
    }
    else 
    {
        ZMPT_Veff = 0;
    }

    ZMPT_Veff_New = map(ZMPT_Veff,4130,5980,0,241);
    Serial.print("Voltage: ");
    Serial.println(ZMPT_Veff_New);
    ZMPT_MaxD = 0;
    delay(100);
}