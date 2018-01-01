#include <WiFiSupport.h>
#include <DisplayLCD.h>
#include <PowerAC.h>
#include <ControlLoad.h>
#include <BlynkControl.h>
#include <ThingspeakServer.h>

#define PIN_CONTROL_LOAD 2 // D4
#define PIN_CURRENT_AC A0

#define BLYNK_HISTORY_GRAPH_DC_CURRENT_PIN 3 // V3
#define BLYNK_HISTORY_GRAPH_AC_CURRENT_PIN 4 // V4

#define THINGSPEAK_AC_FIELD_CURRENT 3
#define THINGSPEAK_AC_FIELD_WORKING 4
#define THINGSPEAK_AC_FIELD_POWER 5

#define MAX_CURRENT_AMPERE 15

unsigned long channelNumberThingspeak = 382411;
const char* writeAPIKeyThingspeak = "MNM4PVW6OK72MSFR";
char authBlynk[] = "8125642efd0a4fdc98bbeaaa760405b0";

WiFiSupport WiFiConnect;
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
    float ampereCurrent = AC.getCurrent();
    float waltPower = AC.getPower(ampereCurrent);
    bool statusLoad = Load.isStatusControl(ampereCurrent, MAX_CURRENT_AMPERE);

    Load.control(statusLoad);

    String textCurrent = String(ampereCurrent) + "A";
    String textPower = String(waltPower) + "W";
    LCD.text("Load AC", textCurrent + " " + textPower);

    BlynkApp.textLCD("Load AC", textCurrent + " " + textPower);
    BlynkApp.sendStatus(statusLoad);
    BlynkApp.send(BLYNK_HISTORY_GRAPH_AC_CURRENT_PIN, ampereCurrent);

    Server.set(THINGSPEAK_AC_FIELD_CURRENT, ampereCurrent);
    Server.set(THINGSPEAK_AC_FIELD_WORKING, statusLoad);
    Server.set(THINGSPEAK_AC_FIELD_POWER, waltPower);
    Server.send();

    BlynkApp.delay(15000);
    BlynkApp.run();
}

