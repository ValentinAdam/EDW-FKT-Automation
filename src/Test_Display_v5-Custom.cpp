// // #include <Arduino.h>
// // #include "DisplayController.h"


// // #define Display_Columns 16
// // #define Display_Rows    2
// // #define Display_Address 0x3F


// // DisplayController displayLCD(Display_Columns, Display_Rows, Display_Address);


// // void setup() 
// // {
// //     Serial.begin(115200);
// //     displayLCD.initialize();
// // }


// // void loop() 
// // {
// //     displayLCD.printPASS();
// //     delay(3000);

// //     displayLCD.printFAIL();
// //     delay(3000);
// // }







// #include <Arduino.h>
// #include "ButtonCounter.h"
// #include "DisplayController.h"

// #define PIN_Button_Count 13
// #define Display_Columns 16
// #define Display_Rows    2
// #define Display_Address 0x3F
// #define Button_Count_Limit_Presses 10
// #define Button_Count_Limit_Time 10000

// DisplayController displayLCD(Display_Columns, Display_Rows, Display_Address);
// ButtonCounter myButtonCounter(PIN_Button_Count);

// void setup() 
// {
//     Serial.begin(115200);
//     myButtonCounter.initialize();
//     displayLCD.initialize();
// }

// void loop() 
// {
//     start:
//     displayLCD.printFirstRow("Start program");
//     delay(1500);
//     goto counter;

//     counter:
//     displayLCD.printFirstRow("Begin counting");
//     bool button_counter_value = myButtonCounter.countButtonPresses(Button_Count_Limit_Presses, Button_Count_Limit_Time);
//     if (button_counter_value == true) 
//     {
//         Serial.println("Button successfully pressed!");
//         displayLCD.printPASS();
//         goto end;
//     }
//     else
//     {
//         Serial.println("Error. Time expired. Button not pressed successfully");
//         displayLCD.printFAIL();
//         goto end;
//     }

//     end:
//     Serial.println("END OF THE PROGRAM");
//     delay(1500);
// }
