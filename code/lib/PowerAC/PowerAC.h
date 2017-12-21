#ifndef PowerAC_h
#define PowerAC_h

#include <Arduino.h>
#include "Configuration.h"

class PowerAC {
private:
    unsigned char _current_pin;
    float _milli_voltage_offset, _sensitivity;
    unsigned short int _number_sample;
    float _voltage = 220.0;
    float _cosphi = 0.86;

public:
    PowerAC(unsigned char current_pin, float milli_voltage_offset, float sensitivity, unsigned short int number_sample);
    float getCurrent();
    float getPower(float current);
    float getTime(unsigned long milli);
    float getEnergy(float power, float timeWorking);
};
#endif
