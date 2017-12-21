#include "ThingspeakServer.h"
#include <ESP8266WiFi.h>
WiFiClient  client;

ThingspeakServer::ThingspeakServer(unsigned long channelNumber, const char* writeAPIKey) {
    _channelNumber = channelNumber;
    _writeAPIKey = writeAPIKey;
}

void ThingspeakServer::init() {
    ThingSpeak.begin(client);
}

void ThingspeakServer::send(unsigned char field, float value) {
    ThingSpeak.writeField(_channelNumber, field, value, _writeAPIKey);
}

void ThingspeakServer::send() {
    ThingSpeak.writeFields(_channelNumber, _writeAPIKey);
}

void ThingspeakServer::set(unsigned char field, float value) {
    ThingSpeak.setField(field, value);
}
