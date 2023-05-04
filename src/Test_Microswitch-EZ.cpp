// /*
//  * This ESP32 code is created by esp32io.com
//  *
//  * This ESP32 code is released in the public domain
//  *
//  * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-button-debounce
//  */

// #include <ezButton.h>

// #define DEBOUNCE_TIME 50 // the debounce time in millisecond, increase this time if it still chatters

// ezButton button(13); // create ezButton object that attach to pin GIOP21

// void setup() {
//   Serial.begin(115200);
//   button.setDebounceTime(DEBOUNCE_TIME); // set debounce time to 50 milliseconds
// }

// void loop() {
//   button.loop(); // MUST call the loop() function first

//   if (button.isPressed())
//     Serial.println("The button is pressed");

//   if (button.isReleased())
//     Serial.println("The button is released");
// }
