#ifndef DisplayLCD_h
#define DisplayLCD_h

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Configuration.h"

class DisplayLCD {
private:
    void _text(String text, byte lineNumber);

public:
    DisplayLCD();

    void init();
    void text(String text_line1, String text_line2);
    void text(byte column, byte row, String text);
};

#endif
