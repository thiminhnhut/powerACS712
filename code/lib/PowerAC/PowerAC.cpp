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

    unsigned int minValue = 1024, maxValue = 0, deltaValue;

    uint32_t start_time = millis();
    while (millis() - start_time < 1000) {
        unsigned short int _adc_value = analogRead(_current_pin);

        if (_adc_value > maxValue) {
            maxValue = _adc_value;
        }

        if (_adc_value < minValue) {
            minValue = _adc_value;
        }
    }

    if (maxValue - minValue <= 2) {
        deltaValue = 0;
    } else {
        deltaValue = maxValue - minValue;
    }

    float _voltage = _InitACS712_AC._kVoltage*deltaValue*5.0/1024.0;

    Serial.println("Min = " + String(minValue) + " Max = " + String(maxValue));

    float _ampereCurrent = (_voltage*sqrt(2)*1000.0)/_InitACS712_AC._sensitivity;

    return _ampereCurrent;
}

float PowerAC::getPower(float current) {
    return current*_voltage*_cosphi;
}

float PowerAC::getEnergy(float power, float timeWorking) {
    return power*timeWorking;
}
