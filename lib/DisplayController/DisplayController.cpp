#include "Arduino.h"
#include "DisplayController.h"

DisplayController::DisplayController(int columns, int rows, int address) : lcdColumns(columns), lcdRows(rows), lcd(address, columns, rows) {}

void DisplayController::initialize() 
{
    lcd.init();
    lcd.backlight();
}

void DisplayController::printFirstRow(const String& message) 
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
    Serial.println(message);
}

void DisplayController::printSecondRow(const String& message) 
{
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(message);
    Serial.println(message);
}

void DisplayController::printSecondRowNoClear(const String& message) 
{
    lcd.setCursor(0, 1);
    lcd.print(message);
    Serial.println(message);
}

void DisplayController::printBothRows(const String& message1, const String& message2) 
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message1);
    Serial.println(message1);
    lcd.setCursor(0, 1);
    lcd.print(message2);
    Serial.println(message2);
}
