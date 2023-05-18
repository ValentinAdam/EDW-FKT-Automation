// #include "DHT.h"

// #define DHT_TYPE    11
// #define DHT_PIN     19
// #define RELAY_PIN   18
// #define BUZZER_PIN  15

// DHT dht(DHT_PIN, DHT_TYPE);

// void setup()
// {
//     Serial.begin(115200);
//     delay(2000);
//     pinMode(RELAY_PIN, OUTPUT);
//     pinMode(BUZZER_PIN, OUTPUT);
//     dht.begin();
//     // digitalWrite(BUZZER_PIN, HIGH);      //turn relay off
//     tone(BUZZER_PIN,100);               //turn buzzer on
// }

// void loop()
// {
//     // digitalWrite(RELAY_PIN, HIGH);      //turn relay off
//     digitalWrite(RELAY_PIN, LOW);       //turn relay on
//     Serial.println("RELAY ON");

//     int humi = dht.readHumidity();      //read humidity
//     float temp = dht.readTemperature(); //read temperature
//     Serial.print("Temperature: ");
//     Serial.print(temp);
//     Serial.println("ºC ");
//     Serial.print("Humidity: ");
//     Serial.print(humi);
//     Serial.println("%");
//     delay(2000);

//     digitalWrite(RELAY_PIN, HIGH);      //turn relay off
//     // digitalWrite(RELAY_PIN, LOW);       //turn relay on
//     Serial.println("RELAY OFF");
//     // noTone(BUZZER_PIN);                 //turn buzzer off
//     delay(2000);
// }

// // NO --> alimentare ESP
// // COM --> alimentare buzzer
