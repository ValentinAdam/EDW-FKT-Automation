// #include"ButtonCounter.h"
// #include<Arduino.h>
// #define PIN_Optical_Count       22
// int BttnPress = 0;
// #define Button_Count_Limit_Presses      10
// #define Button_Count_Limit_Time         30000
// ButtonCounter opticalCounter(PIN_Optical_Count);
// void setup()
// {
//     Serial.begin(115200);
//     pinMode(PIN_Optical_Count, INPUT);
// }

// void loop()
// {
// bool checking_optical_rotation = opticalCounter.countButtonPresses(Button_Count_Limit_Presses, Button_Count_Limit_Time);
// Serial.println("PASS!!");
// delay(3500);
// }