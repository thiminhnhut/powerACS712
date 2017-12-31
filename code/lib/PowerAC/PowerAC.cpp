#include "PowerAC.h"

PowerAC::PowerAC(unsigned char current_pin, unsigned char type_sensor_current, float analogMax) {
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

// float PowerAC::getCurrent() {
//     return random(1, 20) + 0.15;
// }

float PowerAC::getCurrent() {
    unsigned short int _maxPointPeak = 0;
    unsigned short int _adc_value_average = 0;
    for (int i = 0; i < _number_sample; i++) {
        unsigned short int _adc_value = analogRead(_current_pin);
        _adc_value_average += _adc_value;
        if (_adc_value > _maxPointPeak) {
            _maxPointPeak = _adc_value;
        }
    }
    float _milliVoltage = _maxPointPeak*5.0*1000.0/1024.0;
    float _ampereCurrent = (_milliVoltage - _milli_voltage_offset)/(_sensitivity*sqrt(2));
    return _ampereCurrent;
}

float PowerAC::getPower(float current) {
    return current*_voltage*_cosphi;
}

float PowerAC::getEnergy(float power, float timeWorking) {
    return power*timeWorking;
}
