// #include <Arduino.h>

// #define PIN_Voltmeter 13

// double ZMPT_Value = 0;
// double ZMPT_Array[100];
// double ZMPT_Array_Max = 0;
// double ZMPT_Voltage_Max = 0;
// double ZMPT_Voltage_Effective_Determined = 0;
// double ZMPT_Voltage_Effective_Calculated = 0;
// double ZMPT_Voltage_Value = 0;

// void setup() 
// {
//     Serial.begin(115200);
// }

// void loop() 
// {
//     for (int i = 0; i < 100; i++) 
//     {
//         ZMPT_Value = analogRead(PIN_Voltmeter);
//         if (ZMPT_Value > 511) 
//         {
//             ZMPT_Array[i] = ZMPT_Value;
//         }
//         else 
//         {
//             ZMPT_Array[i] = 0;
//         }
//         delay(1);
//     }

//     ZMPT_Array_Max = 0;

//     for (int i = 0; i < 100; i++)
//     {
//         if (ZMPT_Array[i] > ZMPT_Array_Max)
//         {
//             ZMPT_Array_Max = ZMPT_Array[i];
//         }
//     ZMPT_Array[i] = 0;
//     }

//     if (ZMPT_Array_Max != 0) 
//     {
//         ZMPT_Voltage_Max = ZMPT_Array_Max;
//         ZMPT_Voltage_Effective_Determined = ZMPT_Voltage_Max / sqrt(2);
//         ZMPT_Voltage_Effective_Calculated = (((ZMPT_Voltage_Effective_Determined - 420.76) / -90.24) * -210.2) + 210.2;
//     }
//     else 
//     {
//         ZMPT_Voltage_Effective_Calculated = 0;
//     }

//     ZMPT_Voltage_Value = map(ZMPT_Voltage_Effective_Calculated, 4130, 5980, 0, 241);
//     Serial.print("Voltage: ");
//     Serial.println(ZMPT_Voltage_Value);
//     ZMPT_Voltage_Max = 0;
//     delay(100);
// }