#include "WiFiSupport.h"


WiFiSupport::WiFiSupport() {

}

void WiFiSupport::begin(const char *ssid, const char *password) {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void WiFiSupport::_smartConfig() {
    WiFi.mode(WIFI_STA);
    delay(5000);

    int cnt = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if (cnt++ >= 10) {
            WiFi.beginSmartConfig();
            while (true) {
                delay(1000);
                if (WiFi.smartConfigDone()) {
                    Serial.println();
                    Serial.println("SmartConfig: Success");
                    break;
                }
                Serial.print("|");
            }
        }
    }
}

void WiFiSupport::smartConfig() {
    _smartConfig();

    WiFi.printDiag(Serial);
}

void WiFiSupport::smartConfig(unsigned char ledStatus, bool status) {
    unsigned char active, inactive;
    if (status) {
        active = HIGH;
        inactive = LOW;
    } else {
        active = LOW;
        inactive = HIGH;
    }

    pinMode(ledStatus, OUTPUT);
    digitalWrite(ledStatus, active);
    _smartConfig();
    digitalWrite(ledStatus, inactive);

    WiFi.printDiag(Serial);
}
