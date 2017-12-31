#ifndef PowerDC_h
#define PowerDC_h

#include <Arduino.h>

struct InitACS712_DC {
    float _kVoltage, _sensitivity;
};

class PowerDC {
private:
    unsigned char _current_pin;
    unsigned char _type_sensor_current;
    float _analogMax;
    float _milli_voltage_offset = 2500.0;

    InitACS712_DC _init();

public:
    PowerDC(unsigned char current_pin, unsigned char type_sensor_current, float analogMax);
    float getCurrent();
};
#endif
