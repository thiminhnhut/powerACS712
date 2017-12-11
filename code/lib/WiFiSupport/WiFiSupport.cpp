#include "WiFiSupport.h"


WiFiSupport::WiFiSupport() {

}

void WiFiSupport::smartConfig() {
    WiFi.mode(WIFI_STA);

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

    WiFi.printDiag(Serial);
}
