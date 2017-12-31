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
#include <WiFiSupport.h>
#include <DisplayLCD.h>
#include <PowerDC.h>
#include <PowerAC.h>
#include <ControlLoad.h>
#include <BlynkControl.h>
#include <ThingspeakServer.h>

#define __PIN_CONTROL_LOAD__ 2 // D4

#define __PIN_CURRENT_DC__ A0
#define __PIN_CURRENT_AC__ A0
#define __MAX_CURRENT_AMPERE__ 15

// Define timer upload
#define __MILLIS_TIME_UPDATE__ 500
#define __MILLIS_TIME_UPLOAD__ 15000

// Define Blynk App
#define __BLYNK_HISTORY_GRAPH_DC_CURRENT_PIN__ 3 // V3
#define __BLYNK_HISTORY_GRAPH_AC_CURRENT_PIN__ 4 // V4

// Define ThingSpeak Web Server
#define __THINGSPEAK_DC_FIELD_CURRENT__ 1
#define __THINGSPEAK_DC_FIELD_WORKING__ 2
#define __THINGSPEAK_AC_FIELD_CURRENT__ 3
#define __THINGSPEAK_AC_FIELD_WORKING__ 4
#define __THINGSPEAK_AC_FIELD_POWER__ 5

unsigned long channelNumberThingspeak = 382411;
const char* writeAPIKeyThingspeak = "MNM4PVW6OK72MSFR";
char authBlynk[] = "8125642efd0a4fdc98bbeaaa760405b0";

// Object Initation
WiFiSupport WiFiConnect;
PowerDC DC(__PIN_CURRENT_DC__, 20, 3.3);
PowerAC AC(__PIN_CURRENT_AC__, 20, 3.3);
DisplayLCD LCD;
ControlLoad Load(__PIN_CONTROL_LOAD__);
BlynkControl BlynkApp;
ThingspeakServer Server(channelNumberThingspeak, writeAPIKeyThingspeak);

// Function prototype
void controlCurrentDC();
void controlCurrentAC();

void setup() {
    Serial.begin(115200);

    WiFiConnect.smartConfig(LED_BUILTIN, false);

    BlynkApp.init(authBlynk);

    Server.init();

    LCD.init();
}

void loop() {
    // controlCurrentDC();
    controlCurrentAC();
    BlynkApp.run();
    BlynkApp.delay(__MILLIS_TIME_UPDATE__);
}

void controlCurrentDC() {
    float _ampereCurrent = DC.getCurrent();
    bool _isControlLoad = Load.isStatusControl(_ampereCurrent, __MAX_CURRENT_AMPERE__);

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

void controlCurrentAC() {
    float _ampereCurrent = AC.getCurrent();
    float _power = AC.getPower(_ampereCurrent);
    bool _isControlLoad = Load.isStatusControl(_ampereCurrent, __MAX_CURRENT_AMPERE__);

    Load.control(_isControlLoad);

    String textCurrent = String(_ampereCurrent) + "A";
    String textPower = String(_power) + "W";

    LCD.text("Load AC", textCurrent + " " + textPower);

    BlynkApp.textLCD("Load AC", textCurrent + " " + textPower);
    BlynkApp.sendStatus(_isControlLoad);
    BlynkApp.send(__BLYNK_HISTORY_GRAPH_AC_CURRENT_PIN__, _ampereCurrent);

    Server.set(__THINGSPEAK_AC_FIELD_CURRENT__, _ampereCurrent);
    Server.set(__THINGSPEAK_AC_FIELD_WORKING__, _isControlLoad);
    Server.set(__THINGSPEAK_AC_FIELD_POWER__, _power);
    Server.send();

    BlynkApp.delay(__MILLIS_TIME_UPLOAD__);
}
