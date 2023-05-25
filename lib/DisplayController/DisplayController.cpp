#include "Arduino.h"
#include "DisplayController.h"

byte customP11P21A11A21S11[8] = {
	0b11111,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000
};

byte customP12A12A22[8] = {
	0b11111,
	0b00001,
	0b00001,
	0b00001,
	0b00001,
	0b00001,
	0b00001,
	0b00001
};

byte customP22S12F12[8] = {
	0b11111,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

byte customS21[8] = {
	0b11111,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b11111
};

byte customS22[8] = {
	0b11111,
	0b00001,
	0b00001,
	0b00001,
	0b00001,
	0b00001,
	0b00001,
	0b11111
};

byte customI11I21L11[8] = {
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000
};

byte customL21[8] = {
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b11111
};

byte customL22[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b11111
};


DisplayController::DisplayController(int columns, int rows, int address) : lcdColumns(columns), lcdRows(rows), lcd(address, columns, rows) {}


void DisplayController::initialize() 
{
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, customP11P21A11A21S11);
    lcd.createChar(1, customP12A12A22);
    lcd.createChar(2, customP22S12F12);
    lcd.createChar(3, customS21);
    lcd.createChar(4, customS22);
    lcd.createChar(5, customI11I21L11);
    lcd.createChar(6, customL21);
    lcd.createChar(7, customL22);
}

void DisplayController::clear()
{
	lcd.clear();
}


void DisplayController::printPASS()
{
    lcd.clear();
    lcd.setCursor(0, 0);
	lcd.write(byte(0));
	lcd.write(byte(1));
    lcd.setCursor(3, 0);
	lcd.write(byte(0));
	lcd.write(byte(1));
    lcd.setCursor(6, 0);
	lcd.write(byte(0));
	lcd.write(byte(2));
    lcd.setCursor(9, 0);
	lcd.write(byte(0));
	lcd.write(byte(2));

    lcd.setCursor(0, 1);
	lcd.write(byte(0));
	lcd.write(byte(2));
    lcd.setCursor(3, 1);
	lcd.write(byte(0));	
	lcd.write(byte(1));	
    lcd.setCursor(6, 1);
	lcd.write(byte(3));	
	lcd.write(byte(4));
    lcd.setCursor(9, 1);
	lcd.write(byte(3));	
	lcd.write(byte(4));	
    Serial.println("Unit PASS !");
}


void DisplayController::printFAIL()
{
    lcd.clear();
    lcd.setCursor(0, 0);
	lcd.write(byte(0));
	lcd.write(byte(2));
    lcd.setCursor(3, 0);
	lcd.write(byte(0));
	lcd.write(byte(1));
    lcd.setCursor(6, 0);
	lcd.write(byte(5));
    lcd.setCursor(8, 0);
	lcd.write(byte(5));

    lcd.setCursor(0, 1);
	lcd.write(byte(0));
	lcd.write(byte(2));
    lcd.setCursor(3, 1);
	lcd.write(byte(0));	
	lcd.write(byte(1));	
    lcd.setCursor(6, 1);
	lcd.write(byte(5));	
    lcd.setCursor(8, 1);
	lcd.write(byte(6));	
	lcd.write(byte(7));	
    Serial.println("Unit FAIL !");	
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
