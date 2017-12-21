#include "PowerDC.h"

PowerDC::PowerDC(unsigned char current_pin, float milli_voltage_offset, float sensitivity) {
    _current_pin = current_pin;
    _milli_voltage_offset = milli_voltage_offset;
    _sensitivity = sensitivity;
}

#ifdef __MODE_NOT_SENSOR__
float PowerDC::getCurrent() {
    return random(1, __CURRENT_SENSOR_SIMULATION__) + 0.55;
}
#else
float PowerDC::getCurrent() {
    unsigned short int _adc_value = analogRead(_current_pin);
    float _milliVoltage = _adc_value*5.0*1000.0/1024.0;
    float _ampereCurrent = (_milliVoltage - _milli_voltage_offset)/_sensitivity;
    return _ampereCurrent;
}
#endif
