#ifndef PowerAC_h
#define PowerAC_h

#include <Arduino.h>
#include "Configuration.h"

class PowerAC {
private:
    unsigned char _current_pin;
    float _milli_voltage_offset, _sensitivity;
    unsigned short int _number_sample;

public:
    PowerAC(float milli_voltage_offset, float sensitivity, unsigned short int number_sample);
    void setPin(unsigned char current_pin);
    float getCurrent();
};
#endif
