#ifndef PowerAC_h
#define PowerAC_h

#include <Arduino.h>


struct InitACS712_AC {
    float _kVoltage, _sensitivity;
};

class PowerAC {
private:
    unsigned char _current_pin;
    unsigned char _type_sensor_current;
    float _analogMax;
    float _voltage = 220.0;
    float _cosphi = 0.86;

    InitACS712_AC _init();

public:
    PowerAC(unsigned char current_pin, unsigned char type_sensor_current, float analogMax);
    float getCurrent();
    float getPower(float current);
    float getEnergy(float power, float timeWorking);
};
#endif
