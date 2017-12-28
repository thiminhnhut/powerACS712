#ifndef ThingspeakServer_h
#define ThingspeakServer_h

#include <Arduino.h>
#include <ThingSpeak.h>

class ThingspeakServer {
private:
    unsigned long _channelNumber;
    const char* _writeAPIKey;

public:
    ThingspeakServer(unsigned long channelNumber, const char* writeAPIKey);
    void init();
    void send(unsigned char field, float value);
    void send();
    void set(unsigned char field, float value);
};

#endif
