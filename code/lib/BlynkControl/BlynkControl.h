#ifndef Blynk_h
#define  Blynk_h

#include <Arduino.h>
#include "Configuration.h"

class BlynkControl {
private:
    void _textLCD(String text, byte lineNumber);

public:
    BlynkControl();

    void init(const char* auth, const char* ssid, const char* pass);
    void init(const char* auth);

    void run();
    void delay(unsigned long milli);

    void textLCD(String text_line1, String text_line2);
    void textLCD(byte column, byte row, String text);

    void send(int pin, int value);
    bool readControlLoad();

    void sendStatus(bool isStatus);

};

#endif
