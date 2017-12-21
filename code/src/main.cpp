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
#include "ThingspeakServer.h"

unsigned long channelNumberThingspeak = 382411;
const char* writeAPIKeyThingspeak = "MNM4PVW6OK72MSFR";
char authBlynk[] = "8125642efd0a4fdc98bbeaaa760405b0";

// Object Initation
WiFiSupport WiFiConnect;
PowerDC DC(__PIN_CURRENT_DC__, __MILLIS_VOLTAGE_OFFSET__, __SENSITIVITY__);
PowerAC AC(__PIN_CURRENT_AC__, __MILLIS_VOLTAGE_OFFSET__, __SENSITIVITY__, __NUMBER_SAMPLE__);
DisplayLCD LCD;
ControlLoad Load(__PIN_CONTROL_LOAD__);
BlynkControl BlynkApp;
ThingspeakServer Server(channelNumberThingspeak, writeAPIKeyThingspeak);

// Function prototype
void controlCurrentDC(bool _isControlLoadBlynk);
void controlCurrentAC(bool _isControlLoadBlynk);

// Variable Declaration
bool isControlLoadBlynk = false;

void setup() {
    Serial.begin(__BAUD_SERIAL__);

    WiFiConnect.smartConfig();

    BlynkApp.init(authBlynk);

    Server.init();

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

    Load.control(_isControlLoad);

    LCD.text("Current DC", String(_ampereCurrent) + "A");

    BlynkApp.textLCD("Current DC", String(_ampereCurrent) + "A");
    BlynkApp.sendStatus(_isControlLoad);
    BlynkApp.send(__BLYNK_HISTORY_GRAPH_DC_CURRENT_PIN__, _ampereCurrent);

    Server.set(__THINGSPEAK_DC_FIELD_CURRENT__, _ampereCurrent);
    Server.set(__THINGSPEAK_DC_FIELD_WORKING__, _isControlLoad);
    Server.send();

    BlynkApp.delay(__MILLIS_TIME_UPLOAD__);
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

    Load.control(_isControlLoad);

    LCD.text("Current AC", String(_ampereCurrent) + "A");

    String textCurrent = String(_ampereCurrent) + "A";
    String textPower = String(_power) + "W";
    BlynkApp.textLCD("Load AC", textCurrent + " " + textPower);
    BlynkApp.sendStatus(_isControlLoad);
    BlynkApp.send(__BLYNK_HISTORY_GRAPH_AC_CURRENT_PIN__, _ampereCurrent);

    Server.set(__THINGSPEAK_AC_FIELD_CURRENT__, _ampereCurrent);
    Server.set(__THINGSPEAK_AC_FIELD_WORKING__, _isControlLoad);
    Server.set(__THINGSPEAK_AC_FIELD_POWER__, _power);
    Server.send();

    BlynkApp.delay(__MILLIS_TIME_UPLOAD__);
}
