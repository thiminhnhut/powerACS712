#ifndef WiFiSupport_h
#define WiFiSuport_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

class WiFiSupport {
private:
    void _smartConfig();

public:
    WiFiSupport();
    void smartConfig();
    void smartConfig(unsigned char ledStatus, bool status);
    void begin(const char *ssid, const char *password);
};
#endif
