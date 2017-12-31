#ifndef PowerDC_h
#define PowerDC_h

#include <Arduino.h>

class PowerDC {
private:
    unsigned char _current_pin;
    float _kVoltage;
    float _milli_voltage_offset = 2500.0;
    float _sensitivity;

public:
    PowerDC(unsigned char current_pin, unsigned char type_sensor_current, float analogMax);
    float getCurrent();
};
#endif
