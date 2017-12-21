#include "PowerAC.h"

PowerAC::PowerAC(unsigned char current_pin, float milli_voltage_offset, float sensitivity, unsigned short int number_sample) {
    _current_pin = current_pin;
    _milli_voltage_offset = milli_voltage_offset;
    _sensitivity = sensitivity;
    _number_sample = number_sample;
}

#ifdef __MODE_NOT_SENSOR__
float PowerAC::getCurrent() {
    return random(1, __CURRENT_SENSOR_SIMULATION__) + 0.15;
}
#else
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
#endif

float PowerAC::getPower(float current) {
    return current*_voltage*_cosphi;
}

float PowerAC::getTime(unsigned long milli) {
    return (milli - millis())/1000.0;
}

float PowerAC::getEnergy(float power, float timeWorking) {
    return power*timeWorking;
}
