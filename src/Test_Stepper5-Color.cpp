// #include <Arduino.h>
// #include <Stepper.h>

// #define PIN_Stepper1    26
// #define PIN_Stepper2    25
// #define PIN_Stepper3    33
// #define PIN_Stepper4    32
// #define PIN_Microswitch 13
// #define PIN_Door        14
// #define PIN_Buzzer      27
// #define PIN_Color_S0    19
// #define PIN_Color_S1    18
// #define PIN_Color_S2    17
// #define PIN_Color_S3    16
// #define PIN_Color_Out   23

// const double stepsPerRevolution = 2037.8864;                //    number of steps per revolution = 2037.8864
// const double degreePerStep      = stepsPerRevolution/360;   //    celsius degree per step
// const double stepsLeftToRight   = 240*degreePerStep;        //    steps for 240 celsius degree
// const double stepsCenterToLeft  = -120*degreePerStep;       //    steps for 120 celsius degree
// const double stepsRightToCenter = -120*degreePerStep;       //    negative steps for 120 celsius degree
// int led_red_frequency       = 0;
// int led_green_frequency     = 0;
// int led_blue_frequency      = 0;
// int led_yellow_frequency    = 0;
// int led_red_value           = 0;
// int led_green_value         = 0;
// int led_blue_value          = 0;
// int led_yellow_value        = 0;

// Stepper myStepper(stepsPerRevolution, PIN_Stepper1, PIN_Stepper3, PIN_Stepper2, PIN_Stepper4);


// void setup() 
// {
//     Serial.begin(115200);     //  initialize the serial port
//     myStepper.setSpeed(15);   //  stepper speed in rpm
//     pinMode(PIN_Microswitch, INPUT_PULLUP);
//     pinMode(PIN_Door, INPUT_PULLUP);
//     pinMode(PIN_Buzzer, OUTPUT);
//     pinMode(PIN_Color_S0, OUTPUT);
//     pinMode(PIN_Color_S1, OUTPUT);
//     pinMode(PIN_Color_S2, OUTPUT);
//     pinMode(PIN_Color_S3, OUTPUT);
//     pinMode(PIN_Color_Out, INPUT);
//     digitalWrite(PIN_Color_S0, LOW);   //   Setting           scaling    0%
//     digitalWrite(PIN_Color_S1, LOW);   //           frequency         to 
// }


// void loop() 
// {

//     check_door:   //  Verificare senzor usa
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
//             // goto search_zero;
//             // goto piston1_push;
//             goto check_led_red;
//         }
//     }

// /////////////////////////////////////////////////
// //   //  Apasa buton "Pruftaste"       (PISTON 1)
// /////////////////////////////////////////////////

//     check_led_red:  //  Verificare LED rosu     (SENZOR CULOARE)
//     digitalWrite(PIN_Color_S0, HIGH);   //   Setting           scaling    100%
//     digitalWrite(PIN_Color_S1, HIGH);   //           frequency         to 
//     digitalWrite(PIN_Color_S2, LOW);
//     digitalWrite(PIN_Color_S3, LOW);
//     led_red_frequency = pulseIn(PIN_Color_Out, LOW);
//     led_red_value = map(led_red_frequency, 140, 560, 255,0);    // TO DO
//     Serial.print("Red LED value = ");
//     Serial.println(led_red_value);
//     // if(led_red_value > led_green_value && led_red_value > led_blue_value)
//     if(led_red_value != 0)      // TO DO
//     {
//         Serial.println("RED LED OK !");
//         digitalWrite(PIN_Color_S0, LOW);   //   Setting           scaling    0%
//         digitalWrite(PIN_Color_S1, LOW);   //           frequency         to 
//         // goto piston1_release;
//         goto search_zero;
//     }
//     else
//     {
//         Serial.println("RED LED problem !");
//         digitalWrite(PIN_Color_S0, LOW);   //   Setting           scaling    0%
//         digitalWrite(PIN_Color_S1, LOW);   //           frequency         to 
//         // goto end_routine;
//         while(digitalRead(PIN_Door) == LOW)
//         {
//             Serial.println("Open the door !!!");
//             analogWrite(PIN_Buzzer, HIGH);
//         }
//         analogWrite(PIN_Buzzer, LOW);
//         goto check_door;
//     }        

// /////////////////////////////////////////////////
// //   //  Elibereaza buton "Pruftaste"  (PISTON 1)
// /////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////
// //   //  Apasa potentiometru/stepper   (Ambreiaj ? Piston ?)
// ////////////////////////////////////////////////////////////


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
//     }


//     start_routine:
//     Serial.println("Beginning testing routine");
//     Serial.println("Reading MAX voltage value...");
//     ///////////////////////////////////////////////////////////////////
//     // // Citeste valoarea minima de pe voltmetru  (Multimetru digital)
//     ///////////////////////////////////////////////////////////////////
//     delay(1000);
//     Serial.println("MAX position voltage value is: x");
//     Serial.println("Moving to MIN voltage position...");
//     myStepper.step(stepsLeftToRight);
//     ///////////////////////////////////////////////////////////////////
//     // // Citeste valoarea maxima de pe voltmetru  (Multimetru digital)
//     ///////////////////////////////////////////////////////////////////
//     delay(1000);
//     Serial.println("MIN position voltage value is: y");
//     Serial.println("Moving potentiometer into central position");
//     myStepper.step(stepsRightToCenter);
//     ///////////////////////////////////////////////////////////////////////////
//     // // Potentiometru la centru. Apasa buton "Start Abreinigung".  (PISTON 2)
//     ///////////////////////////////////////////////////////////////////////////

//     check_led_yellow:  //  Verificare LED rosu     (SENZOR CULOARE)
//     digitalWrite(PIN_Color_S0, HIGH);   //   Setting           scaling    100%
//     digitalWrite(PIN_Color_S1, HIGH);   //           frequency         to 
//     digitalWrite(PIN_Color_S2, HIGH);
//     digitalWrite(PIN_Color_S3, LOW);
//     led_yellow_frequency = pulseIn(PIN_Color_Out, LOW);
//     led_yellow_value = map(led_yellow_frequency, 140, 560, 255,0);    // TO DO
//     Serial.print("Yellow LED value = ");
//     Serial.println(led_yellow_value);
//     // if(led_red_value > led_green_value && led_red_value > led_blue_value)
//     if(led_yellow_value != 0)      // TO DO
//     {
//         Serial.println("YELLOW LED OK !");
//         digitalWrite(PIN_Color_S0, LOW);   //   Setting           scaling    0%
//         digitalWrite(PIN_Color_S1, LOW);   //           frequency         to 
//         // goto synchronmotor_check;
//         goto end_routine;
//     }
//     else
//     {
//         Serial.println("YELLOW LED problem !");
//         digitalWrite(PIN_Color_S0, LOW);   //   Setting           scaling    0%
//         digitalWrite(PIN_Color_S1, LOW);   //           frequency         to 
//         // goto end_routine;
//         while(digitalRead(PIN_Door) == LOW)
//         {
//             Serial.println("Open the door !!!");
//             analogWrite(PIN_Buzzer, HIGH);
//         }
//         analogWrite(PIN_Buzzer, LOW);
//         goto check_door;
//     }

//     ///////////////////////////////////////////////////////////////////////////
//     // // Verifica rotirea axului "Synchronmotor" (????????)
//     ///////////////////////////////////////////////////////////////////////////
//     ///////////////////////////////////////////////////////////////////////////
//     // // Potentiometru/stepper este eliberat     (Ambreiaj ? Piston ?)
//     ///////////////////////////////////////////////////////////////////////////
//     delay(1000);
//     Serial.println("End of the program");
//     goto end_routine;


//     end_routine:
//     int door_final_state = digitalRead(PIN_Door);
//     while(door_final_state == LOW)
//     {
//         Serial.println("Open the door !!!");
//         analogWrite(PIN_Buzzer, HIGH);
//     }
//     analogWrite(PIN_Buzzer, LOW);
//     goto check_door;

// }