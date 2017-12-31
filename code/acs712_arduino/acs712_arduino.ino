#include <WiFiSupport.h>
#include <DisplayLCD.h>
#include <PowerDC.h>
#include <PowerAC.h>
#include <ControlLoad.h>
#include <BlynkControl.h>
#include <ThingspeakServer.h>

#define PIN_CONTROL_LOAD 2 // D4
#define PIN_CURRENT_DC A0
#define PIN_CURRENT_AC A0

#define BLYNK_HISTORY_GRAPH_DC_CURRENT_PIN 3 // V3
#define BLYNK_HISTORY_GRAPH_AC_CURRENT_PIN 4 // V4

#define THINGSPEAK_DC_FIELD_CURRENT 1
#define THINGSPEAK_DC_FIELD_WORKING 2
#define THINGSPEAK_AC_FIELD_CURRENT 3
#define THINGSPEAK_AC_FIELD_WORKING 4
#define THINGSPEAK_AC_FIELD_POWER 5

#define MAX_CURRENT_AMPERE 15

unsigned long channelNumberThingspeak = 382411;
const char* writeAPIKeyThingspeak = "MNM4PVW6OK72MSFR";
char authBlynk[] = "8125642efd0a4fdc98bbeaaa760405b0";

WiFiSupport WiFiConnect;
PowerDC DC(PIN_CURRENT_DC, 20, 3.3);
PowerAC AC(PIN_CURRENT_AC, 20, 3.3);
DisplayLCD LCD;
ControlLoad Load(PIN_CONTROL_LOAD);
BlynkControl BlynkApp;
ThingspeakServer Server(channelNumberThingspeak, writeAPIKeyThingspeak);

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
    BlynkApp.delay(500);
}

void controlCurrentDC() {
    float _ampereCurrent = DC.getCurrent();
    bool _isControlLoad = Load.isStatusControl(_ampereCurrent, MAX_CURRENT_AMPERE);

    Load.control(_isControlLoad);

    LCD.text("Current DC", String(_ampereCurrent) + "A");

    BlynkApp.textLCD("Current DC", String(_ampereCurrent) + "A");
    BlynkApp.sendStatus(_isControlLoad);
    BlynkApp.send(BLYNK_HISTORY_GRAPH_DC_CURRENT_PIN, _ampereCurrent);

    Server.set(THINGSPEAK_DC_FIELD_CURRENT, _ampereCurrent);
    Server.set(THINGSPEAK_DC_FIELD_WORKING, _isControlLoad);
    Server.send();

    BlynkApp.delay(15000);
}

void controlCurrentAC() {
    float _ampereCurrent = AC.getCurrent();
    float _waltPower = AC.getPower(_ampereCurrent);
    bool _isControlLoad = Load.isStatusControl(_ampereCurrent, MAX_CURRENT_AMPERE);

    Load.control(_isControlLoad);

    String textCurrent = String(_ampereCurrent) + "A";
    String textPower = String(_waltPower) + "W";

    LCD.text("Load AC", textCurrent + " " + textPower);

    BlynkApp.textLCD("Load AC", textCurrent + " " + textPower);
    BlynkApp.sendStatus(_isControlLoad);
    BlynkApp.send(BLYNK_HISTORY_GRAPH_AC_CURRENT_PIN, _ampereCurrent);

    Server.set(THINGSPEAK_AC_FIELD_CURRENT, _ampereCurrent);
    Server.set(THINGSPEAK_AC_FIELD_WORKING, _isControlLoad);
    Server.set(THINGSPEAK_AC_FIELD_POWER, _waltPower);
    Server.send();

    BlynkApp.delay(15000);
}

