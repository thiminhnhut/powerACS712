#include "PowerAC.h"

PowerAC::PowerAC(unsigned char current_pin, unsigned char type_sensor_current, float analogMax) {
    _current_pin = current_pin;
    _type_sensor_current = type_sensor_current;
    _analogMax = analogMax;
}

InitACS712_AC PowerAC::_init() {
    InitACS712_AC _InitACS712_AC;

    if (_analogMax - 5.0 == 0) {
        _InitACS712_AC._kVoltage = 1.0;
    } else if (_analogMax - 3.3 == 0) {
        _InitACS712_AC._kVoltage = 2.0;
    }

    switch (_type_sensor_current) {
        case 20:
            _InitACS712_AC._sensitivity = 100.0;
            break;
        case 30:
            _InitACS712_AC._sensitivity = 66.0;
            break;
    }

    return _InitACS712_AC;
}

// float PowerAC::getCurrent() {
//     return random(1, 20) + 0.15;
// }

float PowerAC::getCurrent() {
    InitACS712_AC _InitACS712_AC = _init();

    unsigned short int _maxPointPeak = 0;
    for (int i = 0; i < _number_sample; i++) {
        unsigned short int _adc_value = analogRead(_current_pin);
        if (_adc_value > _maxPointPeak) {
            _maxPointPeak = _adc_value;
        }
    }

    float _milliVoltage = _InitACS712_AC._kVoltage*_maxPointPeak*5.0*1000.0/1024.0;
    Serial.println(_milliVoltage);
    float _ampereCurrent = (_milliVoltage - _milli_voltage_offset)/(_InitACS712_AC._sensitivity*sqrt(2));
    return _ampereCurrent;
}

float PowerAC::getPower(float current) {
    return current*_voltage*_cosphi;
}

float PowerAC::getEnergy(float power, float timeWorking) {
    return power*timeWorking;
}
