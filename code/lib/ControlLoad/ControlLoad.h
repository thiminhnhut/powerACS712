#ifndef ControlLoad_h
#define ControlLoad_h

#include <Arduino.h>

class ControlLoad {
private:
    unsigned char _load_pin;
    bool _onLoad = HIGH;
    bool _offLoad = LOW;

public:
    ControlLoad(unsigned char load_pin);
    ControlLoad(unsigned char pin, unsigned char status);
    void on();
    void off();
    bool isStatusControl(float current, float maxCurrent);
    void control(bool isControl);
};
#endif
