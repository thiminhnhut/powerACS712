#include "BlynkControl.h"
#include <ESP8266WiFi.h>
#include "Blynk/BlynkApi.h"
#include <BlynkSimpleEsp8266.h>

#define __BLYNK_LCD_PIN__ 0 // V0
#define __BLYNK_LED_PIN__ 1 // V1
#define __BLYNK_LOAD_PIN__ 2 // V2

WidgetLCD lcdBlynk(__BLYNK_LCD_PIN__);
WidgetLED ledBlynk(__BLYNK_LED_PIN__);

bool isControlLoad;

BlynkControl::BlynkControl() {

}

void BlynkControl::init(const char* auth, const char* ssid, const char* pass) {
    Blynk.begin(auth, ssid, pass);
}

void BlynkControl::init(const char* auth) {
    Blynk.config(auth);
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
    _textLCD(text_line1, 0);
    _textLCD(text_line2, 1);
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

void BlynkControl::sendStatus(bool isStatus) {
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
