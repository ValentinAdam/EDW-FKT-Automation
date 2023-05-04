// #include <Arduino.h>
// #include <Stepper.h>

// #define PIN_Stepper1    26
// #define PIN_Stepper2    25
// #define PIN_Stepper3    33
// #define PIN_Stepper4    32
// #define PIN_Microswitch 13
// #define PIN_Door        14
// #define PIN_Buzzer      27

// const double stepsPerRevolution = 2037.8864;                //    number of steps per revolution = 2037.8864
// const double degreePerStep      = stepsPerRevolution/360;   //    celsius degree per step
// const double stepsLeftToRight   = 240*degreePerStep;        //    steps for 240 celsius degree
// const double stepsCenterToLeft  = -120*degreePerStep;       //    steps for 120 celsius degree
// const double stepsRightToCenter = -120*degreePerStep;       //    negative steps for 120 celsius degree

// Stepper myStepper(stepsPerRevolution, PIN_Stepper1, PIN_Stepper3, PIN_Stepper2, PIN_Stepper4);


// void setup() 
// {
//     Serial.begin(115200);     //  initialize the serial port
//     myStepper.setSpeed(15);   //  stepper speed in rpm
//     pinMode(PIN_Microswitch, INPUT_PULLUP);
//     pinMode(PIN_Door, INPUT_PULLUP);
//     pinMode(PIN_Buzzer, OUTPUT);
// }


// void loop() 
// {

//     check_door:
//     int door_state = digitalRead(PIN_Door);
//     Serial.print("Door state is: ");
//     Serial.println(door_state);
//     Serial.println("Checking if door is open");
//     while(door_state == HIGH)
//     {
//         Serial.println("Door is open");
//         int door_state_check = digitalRead(PIN_Door);
//         if(door_state_check == LOW)
//         {
//             Serial.println("Door is closed !!!");
//             goto search_zero;
//         }
//         // else
//         // {
//         //     Serial.println("Problem with the door");
//         // }
//     }


// //   //  Apasa buton "Pruftaste"       (PISTON 1)
// //   //  Verifica LED rosu             (SENZOR CULOARE 1)
// //   //  Elibereaza buton "Pruftaste"  (PISTON 1)
// //   //  Apasa potentiometru/stepper   (Ambreiaj ? Piston ?)


//     search_zero:
//     Serial.println("Beginning searching the zero point");
//     int microswitch_state = digitalRead(PIN_Microswitch);
//     Serial.print("Microswitch state is: ");
//     Serial.println(microswitch_state);
//     while(microswitch_state == HIGH)
//     {
//         Serial.println("Microswitch not pressed");
//         myStepper.step(-1);
//         Serial.println("Stepper motor moved 1 step to the left");
//         int microswitch_state_check = digitalRead(PIN_Microswitch);
//         if(microswitch_state_check == LOW)
//         {
//             Serial.println("Microswitch is pressed !!!");
//             goto start_routine;
//         }
//         // else
//         // {
//         //     Serial.println("Problem with the microswitch");
//         // }
//     }


//     start_routine:
//     Serial.println("Beginning testing routine");
//     delay(1000);    //    Citeste valoarea de pe voltmetru  (Multimetru digital ? Camera ?)
//     Serial.println("Min position voltmeter value is...");
//     myStepper.step(stepsLeftToRight);
//     delay(1000);    //    Citeste valoarea de pe voltmetru  (Multimetru digital ? Camera ?)
//     Serial.println("Max position voltmeter value is...");
//     myStepper.step(stepsRightToCenter);
//     delay(1000);    //    Potentiometru la centru. Apasa buton "Start Abreinigung".  (PISTON 2)
//                     //    Verifica LED galben.                                       (SENZOR CULOARE 2)
//                     //    Verifica rotirea axului "Synchronmotor" (????????)
//                     //    Potentiometru/stepper este eliberat     (Ambreiaj ? Piston ?)
//     Serial.println("End of the program");
//     // Ridicam usa ? Punem un buzzer ca sa tipe sa deschizi usa si-l oprim cand usa se deschide.
//     goto end_routine;


//     end_routine:
//     while(digitalRead(PIN_Door)==LOW)
//     {
//         Serial.println("Open the door !!!");
//         analogWrite(PIN_Buzzer, HIGH);
//     }
//     analogWrite(PIN_Buzzer, LOW);
//     goto check_door;

// }