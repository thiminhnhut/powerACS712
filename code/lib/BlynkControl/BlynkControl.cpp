#include "BlynkControl.h"
#include <ESP8266WiFi.h>
#include "Blynk/BlynkApi.h"
#include <BlynkSimpleEsp8266.h>

WidgetLCD lcdBlynk(__BLYNK_LCD_PIN__);
WidgetLED ledBlynk(__BLYNK_LED_PIN__);

bool isControlLoad;

BlynkControl::BlynkControl(const char* auth, const char* ssid, const char* pass) {
    _auth = auth;
    _ssid = ssid;
    _pass = pass;
}

BlynkControl::BlynkControl(const char* auth, const char* ssid, const char* pass, int pin) {
    _auth = auth;
    _ssid = ssid;
    _pass = pass;
}

void BlynkControl::init() {
    Blynk.begin(_auth, _ssid, _pass);
}

void BlynkControl::run() {
    Blynk.run();
}

void BlynkControl::delay(unsigned long milli) {
    int end_time = millis() + milli;
    while (millis() < end_time){
        run();
        yield();
    }
}

void BlynkControl::_textLCD(String text, byte lineNumber) {
    unsigned char len_text = text.length();

    if (len_text < 17) {
        byte offset_line = floor((16 - len_text)/2);
        lcdBlynk.print(offset_line, lineNumber, text);
    } else {
        lcdBlynk.print(0, lineNumber, text.substring(0, 15));
    }
}

void BlynkControl::textLCD(String text_line1, String text_line2) {
    lcdBlynk.clear();
    _textLCD(text_line1, __LCD_LINE_1__);
    _textLCD(text_line2, __LCD_LINE_2__);
}

void BlynkControl::textLCD(byte column, byte row, String text) {
    lcdBlynk.clear();
    lcdBlynk.print(column, row, text);
}

void BlynkControl::send(int pin, int value) {
    Blynk.virtualWrite(pin, value);
}

bool BlynkControl::readControlLoad() {
    return isControlLoad;
}

void BlynkControl::status(bool isStatus) {
    if (isStatus) {
        ledBlynk.on();
    } else {
        ledBlynk.off();
    }
}


BLYNK_CONNECTED() {
    Blynk.syncAll();
}

BLYNK_WRITE(__BLYNK_LOAD_PIN__) {
    bool pinValue = param.asInt();
    isControlLoad = pinValue;
}
