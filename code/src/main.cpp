/**
 * @brief Do dong dien AC va DC voi cam bien ACS712
 * @author Thi Minh Nhut - Email: thiminhnhut@gmail.com
 * @date Ngay 23 thang 11 nam 2017
 *
 * References:
 *      + http://microcontrollerslab.com/acs712-current-sensor-interfacing-arduino/
 *      + http://microcontrollerslab.com/ac-current-measurement-acs712-arduino/
 */

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define __SIMULATION__
#define __CURRENT_SENSOR_SIMULATION__
// #define __CURRENT_SENSOR_20A__
// #define __CURRENT_SENSOR_30A__
#define __PIN_CURRENT_DC__ A0
#define __PIN_CURRENT_AC__ A1
#define __LCD_COLUMNS__ 16
#define __LCD_ROWS__ 2
#define __BAUD_SERIAL__ 9600

#ifdef __SIMULATION__
    #define  __ADDRESS_LCD_I2C__ 0x20
#else
    #define  __ADDRESS_LCD_I2C__ 0x27
#endif

#ifdef __CURRENT_SENSOR_SIMULATION__
    #define __SENSITIVITY__ 185.0
#else
    #ifdef __CURRENT_SENSOR_20A__
        #define __SENSITIVITY__ 100.0
    #else
        #ifdef __CURRENT_SENSOR_30A__
            #define __SENSITIVITY__ 66.0
        #endif
    #endif
#endif

#define __MILLI_VOLTAGE_OFFSET__ 2500.0
#define __NUMBER_SAMPLE__ 500

LiquidCrystal_I2C lcd(__ADDRESS_LCD_I2C__, __LCD_COLUMNS__, __LCD_ROWS__);

void initLCD();
void displayInfo();
void displayCurrentDC();
void displayCurrentAC();
float getCurrentDC(unsigned char _pin_adc);
float getCurrentAC(unsigned char _pin_adc);
void displayLCD(String line_one, String line_two);

void setup() {
    Serial.begin(__BAUD_SERIAL__);
    initLCD();
    displayInfo();
}

void loop() {
    // displayCurrentDC();
    displayCurrentAC();
}

void initLCD() {
    lcd.begin();
    lcd.clear();
    lcd.backlight();
}

void displayInfo() {
    displayLCD("Current AC - DC", "H.Nhu - A.Thu");
    delay(2000);
    lcd.clear();
}

void displayCurrentDC() {
    float _ampereCurrent = getCurrentDC(__PIN_CURRENT_DC__);
    displayLCD("Current DC", String(_ampereCurrent) + "A");
    delay(2000);
    lcd.clear();
}

void displayCurrentAC() {
    float _ampereCurrent = getCurrentAC(__PIN_CURRENT_AC__);
    displayLCD("Current AC", String(_ampereCurrent) + "A");
    delay(2000);
    lcd.clear();
}

float getCurrentDC(unsigned char _pin_adc) {
    unsigned short int _adc_value = analogRead(_pin_adc);
    float _milliVoltage = _adc_value*5.0*1000.0/1024.0;
    float _ampereCurrent = (_milliVoltage - __MILLI_VOLTAGE_OFFSET__)/__SENSITIVITY__;
    return _ampereCurrent;
}

float getCurrentAC(unsigned char _pin_adc) {
    unsigned short int _maxPointPeak = 0;
    for (int i = 0; i < __NUMBER_SAMPLE__; i++) {
        unsigned short int _adc_value = analogRead(_pin_adc);
        if (_adc_value > _maxPointPeak) {
            _maxPointPeak = _adc_value;
        }
    }
    float _milliVoltage = _maxPointPeak*5.0*1000.0/1024.0;
    float _ampereCurrent = (_milliVoltage - __MILLI_VOLTAGE_OFFSET__)/(__SENSITIVITY__*sqrt(2));
    return _ampereCurrent;
}

void displayLCD(String line_one, String line_two) {
    lcd.clear();

    unsigned char len_line_one = line_one.length();
    unsigned char len_line_two = line_two.length();

    if (len_line_one < 17) {
        int offset_line_one = floor((16 - len_line_one)/2);
        lcd.setCursor(offset_line_one, 0);
        lcd.print(line_one);
    } else {
        lcd.setCursor(0, 0);
        lcd.print(line_one.substring(0, 15));
    }

    if (len_line_two < 17) {
        int offset_line_two = floor((16 - len_line_two)/2);
        lcd.setCursor(offset_line_two, 1);
        lcd.print(line_two);
    } else {
        lcd.setCursor(0, 1);
        lcd.print(line_two.substring(0, 15));
    }
}
