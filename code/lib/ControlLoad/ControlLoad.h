#ifndef ControlLoad_h
#define ControlLoad_h

#include <Arduino.h>
#include "Configuration.h"

class ControlLoad {
private:
    unsigned char _load_pin;

public:
    ControlLoad();
    void setPin(unsigned char load_pin);
    void control(float current, float maxCurrent);
};
#endif
