#ifndef ControlLoad_h
#define ControlLoad_h

#include <Arduino.h>
#include "Configuration.h"

class ControlLoad {
private:
    unsigned char _load_pin;

public:
    ControlLoad(unsigned char load_pin);
    bool isStatusControl(float current, float maxCurrent);
    void control(bool isControl);
};
#endif
