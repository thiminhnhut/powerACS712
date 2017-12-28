#include "DisplayLCD.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

DisplayLCD::DisplayLCD() {

}

void DisplayLCD::init() {
    lcd.begin();
    lcd.clear();
    lcd.backlight();
}

void DisplayLCD::_text(String text, byte lineNumber) {
    unsigned char len_text = text.length();

    if (len_text < 17) {
        byte offset_line = floor((16 - len_text)/2);
        lcd.setCursor(offset_line, lineNumber);
        lcd.print(text);
    } else {
        lcd.setCursor(0, lineNumber);
        lcd.print(text.substring(0, 15));
    }
}

void DisplayLCD::text(String text_line1, String text_line2) {
    lcd.clear();
    _text(text_line1, 0);
    _text(text_line2, 1);
}

void DisplayLCD::text(byte column, byte row, String text) {
    lcd.clear();
    lcd.setCursor(column, row);
    lcd.print(text);
}
