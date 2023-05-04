// #include <Arduino.h>

// #define MOTOR_PIN_1      A1
// #define MOTOR_PIN_2      A2
// #define MOTOR_PIN_3      A3
// #define MOTOR_PIN_4      A4
// #define POTM_PIN         A5
// #define ONOFF_PIN         9 // LOW starts the motor
// #define DIR_PIN           8 // LOW = rotate CCW, HIGH = rotate CW
// #define ZERO_PIN          6 // Start zero find routine
// #define ZERO_FOUND_PIN    7 // Sensor / switch that defines zero position
// #define ONOFF_LED_PIN     5 // Motor running LED
// #define DIR_LED_PIN       4 // Motor direction LED
// #define PULSES_PER_REV 2048 // Pulses per revolution of blue/metal toy motor

// byte rpm, rpm_old, stepnr;
// unsigned long timeoflaststep;

// void find_zero() {
//   Serial.println("Running CW to find zero sensor");
//   while(digitalRead(ZERO_FOUND_PIN) == HIGH) {
//     if ((micros() - timeoflaststep) > 60000000UL / PULSES_PER_REV) {
//     timeoflaststep = micros();
//     do_one_step();
//     }
//   }
//   Serial.println("Zero sensor found");
// }

// void motor_idle() {
//   digitalWrite(MOTOR_PIN_1,   LOW);
//   digitalWrite(MOTOR_PIN_2,   LOW);
//   digitalWrite(MOTOR_PIN_3,   LOW);
//   digitalWrite(MOTOR_PIN_4,   LOW);
//   digitalWrite(ONOFF_LED_PIN, LOW);
//   dir();
// }

// unsigned long stepinterval() { // calculates step timing based on potmeter input
//   rpm = map(analogRead(POTM_PIN), 0, 1024, 1, 13); // max 12 rpm, else pulses get lost
//   if(rpm != rpm_old) {
//     Serial.println(rpm);
//     rpm_old = rpm;
//   }
//   return 60000000UL / PULSES_PER_REV / rpm; // [us] stepinterval
// }

// byte dir() {
//   byte dir_switch = digitalRead(DIR_PIN);
//   digitalWrite(DIR_LED_PIN, !dir_switch);
//   return dir_switch;
// }

// void do_one_step() { 
//   digitalWrite(ONOFF_LED_PIN, HIGH);

//   if(dir() == 1) stepnr++;
//   else stepnr--;
//   stepnr = stepnr%4;

//   switch (stepnr) { // remembers in which of the 4 phases the motor is
//     case 0:
//       digitalWrite(MOTOR_PIN_1, HIGH);
//       digitalWrite(MOTOR_PIN_2, LOW);
//       digitalWrite(MOTOR_PIN_3, LOW);
//       digitalWrite(MOTOR_PIN_4, LOW);
//     break;
//     case 1:
//       digitalWrite(MOTOR_PIN_1, LOW);
//       digitalWrite(MOTOR_PIN_2, HIGH);
//       digitalWrite(MOTOR_PIN_3, LOW);
//       digitalWrite(MOTOR_PIN_4, LOW);
//     break;
//     case 2:
//       digitalWrite(MOTOR_PIN_1, LOW);
//       digitalWrite(MOTOR_PIN_2, LOW);
//       digitalWrite(MOTOR_PIN_3, HIGH);
//       digitalWrite(MOTOR_PIN_4, LOW);
//     break;
//     case 3:
//       digitalWrite(MOTOR_PIN_1, LOW);
//       digitalWrite(MOTOR_PIN_2, LOW);
//       digitalWrite(MOTOR_PIN_3, LOW);
//       digitalWrite(MOTOR_PIN_4, HIGH);
//     break;
//   }
// }

// void setup() {
//   pinMode(ONOFF_PIN,     INPUT_PULLUP);
//   pinMode(DIR_PIN,       INPUT_PULLUP);
//   pinMode(ZERO_PIN,      INPUT_PULLUP);
//   pinMode(ZERO_FOUND_PIN,INPUT_PULLUP);
//   pinMode(MOTOR_PIN_1,   OUTPUT);
//   pinMode(MOTOR_PIN_2,   OUTPUT);
//   pinMode(MOTOR_PIN_3,   OUTPUT);
//   pinMode(MOTOR_PIN_4,   OUTPUT);
//   pinMode(ONOFF_LED_PIN, OUTPUT);
//   pinMode(DIR_LED_PIN,   OUTPUT);
//   digitalWrite(ONOFF_LED_PIN, LOW);
//   Serial.begin(9600);
//   Serial.print("Don't forget to find zero before operating");
// }

// void loop() {
//   if(digitalRead(ZERO_PIN) == 0) find_zero();

//   while(digitalRead(ONOFF_PIN) == LOW) {
//     if ((micros() - timeoflaststep) > stepinterval()) {
//       timeoflaststep = micros();
//       do_one_step();
//     }
//   }
//   motor_idle();
// }