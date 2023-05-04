// #include <Arduino.h>
// #define S0 23
// #define S1 22
// #define S2 19
// #define S3 21
// #define sensorOut 18
// int frequency = 0;
 
// void setup()
// {
//     pinMode(S0, OUTPUT);
//     pinMode(S1, OUTPUT);
//     pinMode(S2, OUTPUT);
//     pinMode(S3, OUTPUT);
//     pinMode(sensorOut, INPUT);
    
//     // Setting frequency-scaling to 100%
//     digitalWrite(S0,HIGH);
//     digitalWrite(S1,HIGH);
    
//     Serial.begin(115200);
// }
 
// void loop()
// {
//     // Setting Red filtered photodiodes to be read
//     digitalWrite(S2,LOW);
//     digitalWrite(S3,LOW);
//     // Reading the output frequency
//     frequency = pulseIn(sensorOut, LOW);
//     // Remap
//     frequency = map(frequency, 25, 75, 255, 0);
//     // Printing the value on the serial monitor
//     Serial.print("R= ");//printing name
//     Serial.print(frequency);//printing RED color frequency
//     Serial.print(" ");
//     delay(100);

//     // Setting Green filtered photodiodes to be read
//     digitalWrite(S2,HIGH);
//     digitalWrite(S3,HIGH);
//     // Reading the output frequency
//     frequency = pulseIn(sensorOut, LOW);
//     // Remap
//     frequency = map(frequency, 45, 90, 255, 0);
//     // Printing the value on the serial monitor
//     Serial.print("G= ");//printing name
//     Serial.print(frequency);//printing RED color frequency
//     Serial.print(" ");
//     delay(100);
    
//     // Setting Blue filtered photodiodes to be read
//     digitalWrite(S2,LOW);
//     digitalWrite(S3,HIGH);
//     // Reading the output frequency
//     frequency = pulseIn(sensorOut, LOW);
//     // Remap
//     frequency = map(frequency, 30, 85, 255, 0);
//     // Printing the value on the serial monitor
//     Serial.print("B= ");//printing name
//     Serial.print(frequency);//printing RED color frequency
//     Serial.println(" ");
//     delay(100);
// }