// #include <Arduino.h>
// #include <Stepper.h>
// #include <ezButton.h>

// #define PIN_Stepper1    26
// #define PIN_Stepper2    25
// #define PIN_Stepper3    33
// #define PIN_Stepper4    32
// #define PIN_RightSwitch 27
// #define PIN_LeftSwitch  14
// #define DEBOUNCE_TIME   100

// const double stepsPerRevolution = 2037.8864;              //  number of steps per revolution = 2037.8864
// const double degreePerStep      = 360/stepsPerRevolution; //  celsius degree per step
// const double stepsLeftToRight   = 240*degreePerStep;      //  steps for 240 celsius degree
// const double stepsCenterToLeft  = -120*degreePerStep;     //  steps for 120 celsius degree
// const double stepsRightToCenter = -120*degreePerStep;     //  negative steps for 120 celsius degree


// Stepper myStepper(stepsPerRevolution, PIN_Stepper1, PIN_Stepper3, PIN_Stepper2, PIN_Stepper4);
// ezButton limitSwitch_right(PIN_RightSwitch);
// ezButton limitSwitch_left(PIN_LeftSwitch);


// void setup() 
// {
//   Serial.begin(115200);     //  initialize the serial port
//   myStepper.setSpeed(15);   //  stepper speed in rpm
//   limitSwitch_left.setDebounceTime(DEBOUNCE_TIME);
//   limitSwitch_right.setDebounceTime(DEBOUNCE_TIME);
// }


// void loop() 
// {
//   goto begin;
//   begin:
//   limitSwitch_left.loop();
//   limitSwitch_right.loop();

//   //  Apasa buton "Pruftaste"       (PISTON 1)
//   //  Verifica LED rosu             (SENZOR CULOARE 1)
//   //  Elibereaza buton "Pruftaste"  (PISTON 1)
//   //  Apasa potentiometru/stepper   (Ambreiaj ? Piston ?)

//   while(limitSwitch_left.getState() == HIGH)
//   {
//     Serial.println("limitSwitch_left not pressed");
//     myStepper.step(-1);   //  roteste stepper-ul la stanga pana este apasat microswitch-ul
//     if(limitSwitch_left.getState() == LOW)
//     {
//       Serial.println("limitSwitch_left is pressed");
//       break;
//     }
//   }

//   delay(2000);  //  Citeste valoarea de pe voltmetru  (Multimetru digital ? Camera ?)
//   myStepper.step(stepsLeftToRight);
//   delay(2000);  //  Citeste valoarea de pe voltmetru  (Multimetru digital ? Camera ?)
//   myStepper.step(stepsRightToCenter);
//   delay(2000);  //  Potentiometru la centru. Apasa buton "Start Abreinigung".  (PISTON 2)
//                 //  Verifica LED galben.                                       (SENZOR CULOARE 2)
//                 //  Verifica rotirea axului "Synchronmotor" (????????)
//                 //  Potentiometru/stepper este eliberat     (Ambreiaj ? Piston ?)







//   if (limitSwitch_left.isPressed())
//   {
//     Serial.println("limitSwitch_left is pressed");
//   }


//   int state = limitSwitch_left.getState();
//   if(state == HIGH)
//     Serial.println("The limit switch: UNTOUCHED");
//   else
//     Serial.println("The limit switch: TOUCHED");


//   // step one revolution in one direction:
//   Serial.println("Rotating motor clockwise...");
//   myStepper.step(stepsPerRevolution);
//   delay(2000);
//   // step one revolution in the other direction:
//   Serial.println("Rotating motor counterclockwise...");
//   myStepper.step(-stepsPerRevolution);
//   delay(2000);

// }