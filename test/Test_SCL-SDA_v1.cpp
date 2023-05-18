// #include <Arduino.h>
// #include "DisplayController.h"
// #include "ButtonCounter.h"

// #define Display_Columns 16
// #define Display_Rows    2
// #define Display_Adress  0x3F

// #define PIN_Button_Count 16 //  22
// #define Button_Count_Limit_Presses 10
// #define Button_Count_Limit_Time 10000

// // Create an instance of the DisplayController
// DisplayController displayLCD(Display_Columns, Display_Rows, Display_Adress);
// ButtonCounter myButtonCounter(PIN_Button_Count);

// const float test = 123.45F;
// const double test2 = 678.99;

// void setup() 
// {
//     Serial.begin(115200);
//     pinMode(PIN_Button_Count, INPUT_PULLUP);
//     displayLCD.initialize();
// }

// void loop() 
// {
//     // // Print on first row only
//     // displayLCD.printFirstRow("Test1: " + String(test));
//     // delay(2000);

//     // // Print on second row only
//     // displayLCD.printSecondRow("Test2: " + String(test2));
//     // delay(2000);

//     // // Print on both rows
//     // displayLCD.printBothRows("Test1: " + String(test), "Test2: " + String(test2));
//     // delay(2000);





//     start:
//     Serial.println("START OF THE PROGRAM");
//     displayLCD.printFirstRow("Start program");
//     delay(3000);
//     goto counter;


//     counter:
//     Serial.println("Beginning counting");
//     displayLCD.printFirstRow("Start count");
//     bool button_counter_value = myButtonCounter.countButtonPresses(Button_Count_Limit_Presses, Button_Count_Limit_Time);
//     if (button_counter_value == true) 
//     {
//         Serial.println("Button successfully pressed!");
//         displayLCD.printFirstRow("Button pressed");
//         delay(1000);
//         goto end;
//     }
//     else
//     {
//         Serial.println("Error. Time expired. Button not pressed successfully");
//         displayLCD.printFirstRow("Time expired");
//         delay(1000);
//         goto start;
//     }


//     end:
//     Serial.println("END OF THE PROGRAM");
//     displayLCD.printFirstRow("End program");
//     // displayLCD.printSecondRowNoClear("End program");
//     delay(3000);
// }
