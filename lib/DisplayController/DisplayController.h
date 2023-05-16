#ifndef DisplayController_H
#define DisplayController_H

#include <LiquidCrystal_I2C.h>

class DisplayController 
{
    private:
        int lcdColumns;
        int lcdRows;
        LiquidCrystal_I2C lcd;

    public:
        DisplayController(int columns, int rows, int address);
        void initialize();
        void printFirstRow(const String& message);
        void printSecondRow(const String& message);
        void printSecondRowNoClear(const String& message);
        void printBothRows(const String& message1, const String& message2);
};

#endif
