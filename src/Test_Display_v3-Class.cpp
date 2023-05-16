// #include <Arduino.h>
// #include <LiquidCrystal_I2C.h>

// class DisplayClass 
// {
//     private:
//         int lcdColumns;
//         int lcdRows;
//         LiquidCrystal_I2C lcd;

//     public:
//         DisplayClass(int columns, int rows, int address) : lcdColumns(columns), lcdRows(rows), lcd(address, columns, rows) {}

//         void initialize() 
//         {
//             lcd.init();
//             lcd.backlight();
//             Serial.println("LCD Display initialized");
//         }

//         void printFirstRow(const String& message) 
//         {
//             lcd.clear();
//             lcd.setCursor(0, 0);
//             lcd.print(message);
//             Serial.println(message);
//         }

//         void printSecondRow(const String& message) 
//         {
//             lcd.clear();
//             lcd.setCursor(0, 1);
//             lcd.print(message);
//             Serial.println(message);
//         }

//         void printBothRows(const String& message1, const String& message2) 
//         {
//             lcd.clear();
//             lcd.setCursor(0, 0);
//             lcd.print(message1);
//             Serial.println(message1);
//             lcd.setCursor(0, 1);
//             lcd.print(message2);
//             Serial.println(message2);
//         }
// };

// DisplayClass displayLCD(16, 2, 0x3F);
// const double test = 123.45;
// const float test2 = 678.32F;

// void setup() 
// {
//     Serial.begin(115200);
//     displayLCD.initialize();
// }

// void loop() 
// {
//     displayLCD.printFirstRow("Test1: " + String(test));
//     delay(2000);

//     displayLCD.printSecondRow("Test2: " + String(test2));
//     delay(2000);

//     displayLCD.printBothRows("Test1: " + String(test), "Test2: " + String(test2));
//     delay(2000);

//     displayLCD.printFirstRow("It works !");
//     delay(2000);
// }
