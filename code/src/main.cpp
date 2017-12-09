/**
 * @brief Do dong dien AC va DC voi cam bien ACS712
 * @author Thi Minh Nhut - Email: thiminhnhut@gmail.com
 * @date Ngay 23 thang 11 nam 2017
 *
 * References:
 *      + http://microcontrollerslab.com/acs712-current-sensor-interfacing-arduino/
 *      + http://microcontrollerslab.com/ac-current-measurement-acs712-arduino/
 */

#include <Arduino.h>
#include "Configuration.h"
#include "DisplayLCD.h"
#include "PowerDC.h"
#include "PowerAC.h"
#include "ControlLoad.h"

// Object Initation
PowerDC DC(__MILLI_VOLTAGE_OFFSET__, __SENSITIVITY__);
PowerAC AC(__MILLI_VOLTAGE_OFFSET__, __SENSITIVITY__, __NUMBER_SAMPLE__);
DisplayLCD LCD;
ControlLoad Load;

void displayCurrentDC();
void displayCurrentAC();


void setup() {
    Serial.begin(__BAUD_SERIAL__);

    DC.setPin(__PIN_CURRENT_DC__);
    AC.setPin(__PIN_CURRENT_AC__);

    Load.setPin(__PIN_CONTROL_LOAD__);

    LCD.init();
}

void loop() {
    // displayCurrentDC();
    displayCurrentAC();
}

void displayCurrentDC() {
    float _ampereCurrent = DC.getCurrent();
    LCD.text("Current DC", String(_ampereCurrent) + "A");
    Load.control(_ampereCurrent, __MAX_CURRENT_AMPERE__);
    delay(2000);
}

void displayCurrentAC() {
    float _ampereCurrent = AC.getCurrent();
    LCD.text("Current AC", String(_ampereCurrent) + "A");
    Load.control(_ampereCurrent, __MAX_CURRENT_AMPERE__);
    delay(2000);
}
