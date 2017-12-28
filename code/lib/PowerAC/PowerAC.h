#ifndef PowerAC_h
#define PowerAC_h

#include <Arduino.h>



class PowerAC {
private:
    unsigned char _current_pin;
    unsigned char _kVoltage;
    float _sensitivity;
    float _milli_voltage_offset = 2500.0;
    unsigned short int _number_sample = 500;
    float _voltage = 220.0;
    float _cosphi = 0.86;

public:
    PowerAC(unsigned char current_pin, unsigned char type_sensor_current, float analogMax);
    float getCurrent();
    float getPower(float current);
    float getEnergy(float power, float timeWorking);
};
#endif
