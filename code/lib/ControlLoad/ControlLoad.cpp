#include "ControlLoad.h"

ControlLoad::ControlLoad() {

}

void ControlLoad::setPin(unsigned char load_pin) {
    _load_pin = load_pin;
    pinMode(_load_pin, OUTPUT);
}

void ControlLoad::control(float current, float maxCurrent) {
    bool isControl = current >= maxCurrent;
    if (isControl) {
        digitalWrite(_load_pin, __NATIVE_LOAD__);
    } else {
        digitalWrite(_load_pin, __ACTIVE_LOAD__);
    }
}
