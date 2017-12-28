#include "ControlLoad.h"

ControlLoad::ControlLoad(unsigned char load_pin) {
    _load_pin = load_pin;
    pinMode(_load_pin, OUTPUT);
}

ControlLoad::ControlLoad(unsigned char load_pin, unsigned char status) {
    _load_pin = load_pin;
    pinMode(_load_pin, OUTPUT);
    if (status == HIGH) {
        _onLoad = HIGH;
        _offLoad = LOW;
    } else if (status == LOW) {
        _onLoad = LOW;
        _offLoad = HIGH;
    }
}

void ControlLoad::on() {
    digitalWrite(_load_pin, _onLoad);
}

void ControlLoad::off() {
    digitalWrite(_load_pin, _offLoad);
}

bool ControlLoad::isStatusControl(float current, float maxCurrent) {
    return !(current >= maxCurrent);
}

void ControlLoad::control(bool isControl) {
    if (isControl) {
        on();
    } else {
        off();
    }
}
