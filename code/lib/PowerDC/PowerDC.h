#ifndef PowerDC_h
#define PowerDC_h

#include <Arduino.h>
#include "Configuration.h"

class PowerDC {
private:
    unsigned char _current_pin;
    float _milli_voltage_offset, _sensitivity;

public:
    PowerDC(unsigned char current_pin, float milli_voltage_offset, float sensitivity);
    float getCurrent();
};
#endif
