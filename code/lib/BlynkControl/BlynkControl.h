#ifndef Blynk_h
#define  Blynk_h

#include <Arduino.h>
#include "Configuration.h"

class BlynkControl {
private:
    const char* _auth;
    const char* _ssid;
    const char* _pass;
    void _textLCD(String text, byte lineNumber);

public:
    BlynkControl(const char* auth, const char* ssid, const char* pass);
    BlynkControl(const char* auth, const char* ssid, const char* pass, int pin);

    void init();
    void run();
    void delay(unsigned long milli);

    void textLCD(String text_line1, String text_line2);
    void textLCD(byte column, byte row, String text);

    void send(int pin, int value);
    bool readControlLoad();

    void status(bool isStatus);

};

#endif
