#include "PowerDC.h"

PowerDC::PowerDC(unsigned char current_pin, unsigned char type_sensor_current, float analogMax) {
    _current_pin = current_pin;
    _type_sensor_current = type_sensor_current;
    _analogMax = analogMax;
}

InitACS712_DC PowerDC::_init() {
    InitACS712_DC _InitACS712_DC;

    if (_analogMax - 5.0 == 0) {
        _InitACS712_DC._kVoltage = 1.0;
    } else if (_analogMax - 3.3 == 0) {
        _InitACS712_DC._kVoltage = 2.0;
    }

    switch (_type_sensor_current) {
        case 20:
            _InitACS712_DC._sensitivity = 100.0;
            break;
        case 30:
            _InitACS712_DC._sensitivity = 66.0;
            break;
    }

    return _InitACS712_DC;
}
// float PowerDC::getCurrent() {
//     return random(1, 20) + 0.55;
// }

float PowerDC::getCurrent() {
    InitACS712_DC _InitACS712_DC = _init();

    unsigned short int _adc_value = analogRead(_current_pin);
    float _milliVoltage = _InitACS712_DC._kVoltage*_adc_value*5.0*1000.0/1024.0;
    float _ampereCurrent = (_milliVoltage - _milli_voltage_offset)/_InitACS712_DC._sensitivity;
    return _ampereCurrent;
}
