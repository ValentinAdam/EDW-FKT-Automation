// #include <Arduino.h>

// #define PIN_Button      13

// void setup() 
// {
//     Serial.begin(115200);     //  initialize the serial port
//     pinMode(PIN_Button, INPUT_PULLUP);
// }

// void loop() 
// {
//     start:
//     Serial.println("START OF THE PROGRAM");
//     delay(2000);
//     Serial.println("WAITED 2 SECONDS");
//     int count = 0;  // initialize count to 0, static keyword ensures it persists between iterations
//     int flag = 0; // initialize flag to 0
//     unsigned long time_of_button_count = 0; // initialize the time since the button was last pressed to 0
//     goto count_presses;

//     count_presses:
//     time_of_button_count = millis();
//     while (true) // infinite loop
//     {
//         int button_state = digitalRead(PIN_Button);
//         Serial.print("Button state == ");
//         Serial.println(button_state);
//         Serial.print("Counter increment is == ");
//         Serial.println(count);

//         if(button_state == HIGH)
//         {
//             Serial.println("The button is not pressed"); 
//         }
//         else if(button_state == LOW)
//         {
//             Serial.println("The button is pressed");
//             count++; // increment count when the button is pressed
//             if(count == 10) // check if count has reached 10
//             {
//                 Serial.println("Button pressed 10 times!");
//                 flag = 1; // turn on the flag
//                 count = 0; // reset count to 0
//                 break; // break the while loop
//             }
//         }

//         // check if 30 seconds have elapsed since the button was last pressed
//         if (millis() - time_of_button_count >= 30000) 
//         {
//             Serial.println("Timeout: 30 seconds have elapsed since the button was last pressed.");
//             break; // break the while loop
//         }

//         delay(100);
//     }

//     // Code outside the while loop can be executed here
//     if(flag == 1)
//     {
//         Serial.println("Flag is on!");
//         goto final;
//     }


//     final:
//     Serial.println("We've reached the happy ending");
//     delay(1000); // add a delay to prevent the code from running too fast
//     Serial.println("Waited 1 second before going to start");
//     goto start;
// }
