#include "ZMPT101B.h"

#define MIN_MEASURED_VALUE 4130
#define MAX_MEASURED_VALUE 5980
#define MIN_CALIBRATED_VALUE 0
#define MAX_CALIBRATED_VALUE 241

ZMPT101B::ZMPT101B(int PIN) 
{
  _PIN = PIN;
}

double ZMPT101B::getVoltage() 
{
    int number_of_samples = 100;
    int ZMPT_Array[number_of_samples];
    int ZMPT_Array_Max = 0;
    double ZMPT_Measured_Value = 0;
    double ZMPT_Voltage_Max = 0;
    double ZMPT_Voltage_Effective_Determined = 0;
    double ZMPT_Voltage_Effective_Calculated = 0;
    double ZMPT_Voltage_Final_Value = 0;

    for (int i = 0; i < number_of_samples; i++) 
    {
        ZMPT_Measured_Value = analogRead(_PIN);

        if (ZMPT_Measured_Value > 511) 
        {
            ZMPT_Array[i] = ZMPT_Measured_Value;
        }
        else 
        {
            ZMPT_Array[i] = 0;
        }

        delay(1);
    }

    ZMPT_Array_Max = 0;

    for (int i = 0; i < number_of_samples; i++)
    {
        if (ZMPT_Array[i] > ZMPT_Array_Max)
        {
            ZMPT_Array_Max = ZMPT_Array[i];
        }
        ZMPT_Array[i] = 0;
    }

    if (ZMPT_Array_Max != 0) 
    {
        ZMPT_Voltage_Max = ZMPT_Array_Max;
        ZMPT_Voltage_Effective_Determined = ZMPT_Voltage_Max / sqrt(2);
        ZMPT_Voltage_Effective_Calculated = (((ZMPT_Voltage_Effective_Determined - 420.76) / -90.24) * -210.2) + 210.2;
    }
    else 
    {
        ZMPT_Voltage_Effective_Calculated = 0;
    }

    ZMPT_Voltage_Final_Value = map(ZMPT_Voltage_Effective_Calculated, MIN_MEASURED_VALUE, MAX_MEASURED_VALUE, MIN_CALIBRATED_VALUE, MAX_CALIBRATED_VALUE); // MIN/MAX values from calibration
    ZMPT_Voltage_Max = 0;

    return ZMPT_Voltage_Final_Value;
}
