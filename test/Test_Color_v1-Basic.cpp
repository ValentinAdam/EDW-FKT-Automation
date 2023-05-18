// #include <Arduino.h>

// #define PIN_Color_S0         23
// #define PIN_Color_S1         22
// #define PIN_Color_S2         19
// #define PIN_Color_S3         21
// #define PIN_Color_Out        18
// int led_red_frequency       = 0;
// int led_green_frequency     = 0;
// int led_blue_frequency      = 0;
// int led_red_value           = 0;
// int led_green_value         = 0;
// int led_blue_value          = 0;
 
// void setup()
// {
//     pinMode(PIN_Color_S0, OUTPUT);
//     pinMode(PIN_Color_S1, OUTPUT);
//     pinMode(PIN_Color_S2, OUTPUT);
//     pinMode(PIN_Color_S3, OUTPUT);
//     pinMode(PIN_Color_Out, INPUT);
    
//     // // Setting frequency-scaling to 100%
//     // digitalWrite(PIN_Color_S0,HIGH);
//     // digitalWrite(PIN_Color_S1,HIGH);
    
//     Serial.begin(115200);
// }
 
// void loop()
// {
//     // Setting frequency-scaling to 100%
//     Serial.println("Setting frequency-scaling to 100%");
//     digitalWrite(PIN_Color_S0, HIGH);
//     digitalWrite(PIN_Color_S1, HIGH);
//     delay(2000);

//     // Setting Red filtered photodiodes to be read
//     digitalWrite(PIN_Color_S2, LOW);
//     digitalWrite(PIN_Color_S3, LOW);
//     // Reading the output frequency
//     led_red_frequency = pulseIn(PIN_Color_Out, LOW);
//     // Remap
//     led_red_value = map(led_red_frequency, 25, 75, 255, 0);
//     // Printing the value on the serial monitor
//     Serial.print("Red = ");    //printing name
//     Serial.print(led_red_value);    //printing RED color frequency
//     // Serial.print(led_red_frequency);    //printing RED color frequency
//     Serial.print(" ");
//     delay(100);

//     // Setting Green filtered photodiodes to be read
//     digitalWrite(PIN_Color_S2, HIGH);
//     digitalWrite(PIN_Color_S3, HIGH);
//     // Reading the output frequency
//     led_green_frequency = pulseIn(PIN_Color_Out, LOW);
//     // Remap
//     led_green_value = map(led_green_frequency, 45, 90, 255, 0);
//     // Printing the value on the serial monitor
//     Serial.print("Green = ");    //printing name
//     Serial.print(led_green_value);    //printing GREEN color frequency
//     // Serial.print(led_green_frequency);    //printing GREEN color frequency
//     Serial.print(" ");
//     delay(100);
    
//     // Setting Blue filtered photodiodes to be read
//     digitalWrite(PIN_Color_S2, LOW);
//     digitalWrite(PIN_Color_S3, HIGH);
//     // Reading the output frequency
//     led_blue_frequency = pulseIn(PIN_Color_Out, LOW);
//     // Remap
//     led_blue_value = map(led_blue_frequency, 30, 85, 255, 0);
//     // Printing the value on the serial monitor
//     Serial.print("Blue = ");    //printing name
//     Serial.print(led_blue_value);    //printing BLUE color frequency
//     // Serial.print(led_blue_frequency);    //printing BLUE color frequency
//     Serial.println(" ");
//     delay(100);


//     // Setting frequency-scaling to 0%
//     Serial.println("Setting frequency-scaling to 0%");
//     digitalWrite(PIN_Color_S0, LOW);
//     digitalWrite(PIN_Color_S1, LOW);
//     delay(2000);

// }