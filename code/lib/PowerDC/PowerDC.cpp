#include "PowerDC.h"

PowerDC::PowerDC(unsigned char current_pin, unsigned char type_sensor_current, float analogMax) {
    _current_pin = current_pin;

    if (analogMax == 5.0) {
        _kVoltage = 1.0;
    } else if (analogMax == 3.3) {
        _kVoltage = 2.0;
    }

    switch (type_sensor_current) {
        case 20:
            _sensitivity = 100.0;
            break;
        case 30:
            _sensitivity = 66.0;
            break;
    }
}

// float PowerDC::getCurrent() {
//     return random(1, 20) + 0.55;
// }

float PowerDC::getCurrent() {
    unsigned short int _adc_value = analogRead(_current_pin);
    float _milliVoltage = _kVoltage*_adc_value*5.0*1000.0/1024.0;
    float _ampereCurrent = (_milliVoltage - _milli_voltage_offset)/_sensitivity;
    return _ampereCurrent;
}
