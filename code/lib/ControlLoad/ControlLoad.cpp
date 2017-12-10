#include "ControlLoad.h"

ControlLoad::ControlLoad() {

}

void ControlLoad::setPin(unsigned char load_pin) {
    _load_pin = load_pin;
    pinMode(_load_pin, OUTPUT);
}

bool ControlLoad::isStatusControl(float current, float maxCurrent) {
    return !(current >= maxCurrent);
}

void ControlLoad::control(bool isControl) {
    if (isControl) {
        digitalWrite(_load_pin, __ACTIVE_LOAD__);
    } else {
        digitalWrite(_load_pin, __NATIVE_LOAD__);
    }
}
