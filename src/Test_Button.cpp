// #include <Arduino.h>

// #define PIN_Button      14

// void setup() 
// {
//     Serial.begin(115200);     //  initialize the serial port
//     pinMode(PIN_Button, INPUT_PULLUP);
// }


// void loop() 
// {
//     Serial.println("Beginning the program");

//     int button_state = digitalRead(PIN_Button);
//     Serial.println(button_state);

//     if(button_state == HIGH)
//     {
//         Serial.println("The button is OFF"); 
//     }
//     else if(button_state == LOW)
//     {
//         Serial.println("The button is ON");
//     }
//     else
//     {
//         Serial.println("What is this ?");
//     }
//     delay(1000);

// }