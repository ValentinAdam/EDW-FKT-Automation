// #include <Arduino.h>

// #define PIN_Button      13

// volatile int button_press_count = 0;

// hw_timer_t * timer = NULL;

// void IRAM_ATTR handle_interrupt()
// {
//     button_press_count++;
// }

// void IRAM_ATTR check_button_state()
// {
//     int button_state = digitalRead(PIN_Button);
//     if (button_state == LOW) {
//         handle_interrupt();
//     }
// }

// void setup()
// {
//     Serial.begin(115200);     //  initialize the serial port
//     pinMode(PIN_Button, INPUT_PULLUP);

//     timer = timerBegin(0, 80, true);
//     timerAttachInterrupt(timer, &check_button_state, true);
//     timerAlarmWrite(timer, 100000, true);
//     timerAlarmEnable(timer);
// }

// void loop()
// {
//     Serial.println("Hello world");
//     static int prev_button_press_count = 0;

//     if (button_press_count != prev_button_press_count) {
//         Serial.print("Button press count: ");
//         Serial.println(button_press_count);
//         prev_button_press_count = button_press_count;
//     }

//     if (button_press_count >= 10) {
//         Serial.println("10 button presses reached!");
//         button_press_count = 0;
//         loop();
//     }

//     delay(10);

// }
