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
#include "Configuration.h"
#include "WiFiSupport.h"
#include "DisplayLCD.h"
#include "PowerDC.h"
#include "PowerAC.h"
#include "ControlLoad.h"
#include "BlynkControl.h"
char auth[] = "8125642efd0a4fdc98bbeaaa760405b0";

// Object Initation
WiFiSupport WiFiConnect;
PowerDC DC(__MILLIS_VOLTAGE_OFFSET__, __SENSITIVITY__);
PowerAC AC(__MILLIS_VOLTAGE_OFFSET__, __SENSITIVITY__, __NUMBER_SAMPLE__);
DisplayLCD LCD;
ControlLoad Load;
BlynkControl BlynkApp;

// Function prototype
void controlCurrentDC(bool _isControlLoadBlynk);
void controlCurrentAC(bool _isControlLoadBlynk);

// Variable Declaration
bool isControlLoadBlynk = false;

void setup() {
    Serial.begin(__BAUD_SERIAL__);

    WiFiConnect.smartConfig();

    BlynkApp.init(auth);

    DC.setPin(__PIN_CURRENT_DC__);
    AC.setPin(__PIN_CURRENT_AC__);

    Load.setPin(__PIN_CONTROL_LOAD__);

    LCD.init();

}

void loop() {
    isControlLoadBlynk = BlynkApp.readControlLoad();
    // controlCurrentDC(isControlLoadBlynk);
    controlCurrentAC(isControlLoadBlynk);
    BlynkApp.run();
    BlynkApp.delay(__MILLIS_TIME_UPDATE__);
}

void controlCurrentDC(bool _isControlLoadBlynk) {
    float _ampereCurrent;
    bool _isControlLoad;

    if (_isControlLoadBlynk) {
        _ampereCurrent = DC.getCurrent();
        _isControlLoad = Load.isStatusControl(_ampereCurrent, __MAX_CURRENT_AMPERE__);
    } else {
        _ampereCurrent = 0.0;
        _isControlLoad = _isControlLoadBlynk;
    }

    LCD.text("Current DC", String(_ampereCurrent) + "A");

    BlynkApp.textLCD("Current DC", String(_ampereCurrent) + "A");
    BlynkApp.send(__BLYNK_GRAPH_PIN__, _ampereCurrent);
    BlynkApp.send(__BLYNK_HISTORY_GRAPH_CURRENT_PIN__, _ampereCurrent);
    BlynkApp.status(_isControlLoad);

    Load.control(_isControlLoad);
}

void controlCurrentAC(bool _isControlLoadBlynk) {
    float _ampereCurrent, _power, _time, _energy;
    bool _isControlLoad;

    if (_isControlLoadBlynk) {
        _ampereCurrent = AC.getCurrent();
        _isControlLoad = Load.isStatusControl(_ampereCurrent, __MAX_CURRENT_AMPERE__);
    } else {
        _ampereCurrent = 0.0;
        _isControlLoad = _isControlLoadBlynk;
    }

    _power = AC.getPower(_ampereCurrent);
    _time = __MILLIS_TIME_UPDATE__/1000.0;
    _energy = AC.getEnergy(_power, _time);

    LCD.text("Current AC", String(_ampereCurrent) + "A");

    BlynkApp.textLCD("Current AC", String(_ampereCurrent) + "A");
    BlynkApp.send(__BLYNK_GRAPH_PIN__, _ampereCurrent);
    BlynkApp.send(__BLYNK_HISTORY_GRAPH_CURRENT_PIN__, _ampereCurrent);
    BlynkApp.send(__BLYNK_HISTORY_GRAPH_POWER_PIN__, _power);
    BlynkApp.send(__BLYNK_HISTORY_GRAPH_ENERGY_PIN__, _energy);
    BlynkApp.status(_isControlLoad);

    Load.control(_isControlLoad);
}
