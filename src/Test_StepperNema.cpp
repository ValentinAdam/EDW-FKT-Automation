// // Include the Arduino Stepper Library
// #include <Arduino.h>
// #include <Stepper.h>

// #define PIN_Stepper1    32
// #define PIN_Stepper2    33
// #define PIN_Stepper3    25
// #define PIN_Stepper4    26

// const double stepsPerRevolution = 200;                      //    number of steps per revolution
// // const double stepsPerRevolution = 48;                      //    number of steps per revolution
// const double degreePerStep      = stepsPerRevolution/360;   //    celsius degree per step
// const double stepsLeftToRight   = -240*degreePerStep;        //    steps for 240 celsius degree
// const double stepsCenterToLeft  = 120*degreePerStep;       //    steps for 120 celsius degree
// const double stepsRightToCenter = 120*degreePerStep;       //    negative steps for 120 celsius degree

// Stepper myStepper(stepsPerRevolution, PIN_Stepper1, PIN_Stepper2, PIN_Stepper3, PIN_Stepper4);

// void setup()
// {
// 	myStepper.setSpeed(60);
// 	Serial.begin(115200);
// }

// void loop() 
// {
//     // Serial.println("clockwise");
// 	// myStepper.step(stepsPerRevolution);
// 	// delay(500);

// 	Serial.println("stepsCenterToLeft");
// 	myStepper.step(stepsCenterToLeft);
// 	delay(1000);

// 	Serial.println("stepsLeftToRight");
// 	myStepper.step(stepsLeftToRight);
// 	delay(1000);

// 	Serial.println("stepsRightToCenter");
// 	myStepper.step(stepsRightToCenter);
// 	delay(1000);

//     // Serial.println("counterclockwise");
// 	// myStepper.step(-stepsPerRevolution);
// 	// delay(500);
// }