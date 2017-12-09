#ifndef Configuration_h
#define Configuration_h

// Mode Simulation
// #define __SIMULATION__

// Mode Debug
#define __MODE_NOT_SENSOR__

#define __CURRENT_DC__
#define __CURRENT_AC__

#define __PIN_CONTROL_LOAD__ D6
#define __MAX_CURRENT_AMPERE__ 15

#define __PIN_CURRENT_DC__ A0
#define __PIN_CURRENT_AC__ A0

#define __CURRENT_SENSOR_SIMULATION__ 20
// #define __CURRENT_SENSOR_20A__ 20
// #define __CURRENT_SENSOR_30A__ 30

#ifdef __CURRENT_SENSOR_SIMULATION__
    #define __SENSITIVITY__ 185.0
#else
    #ifdef __CURRENT_SENSOR_20A__
        #define __SENSITIVITY__ 100.0
    #else
        #ifdef __CURRENT_SENSOR_30A__
            #define __SENSITIVITY__ 66.0
        #endif
    #endif
#endif

#define __MILLI_VOLTAGE_OFFSET__ 2500.0
#define __NUMBER_SAMPLE__ 500

#define __ACTIVE_LOAD__ HIGH
#define __NATIVE_LOAD__ LOW

#define __LCD_COLUMNS__ 16
#define __LCD_ROWS__ 2
#define __LCD_LINE_1__ 0
#define __LCD_LINE_2__ 1

#ifdef __SIMULATION__
#define  __ADDRESS_LCD_I2C__ 0x20
#else
#define  __ADDRESS_LCD_I2C__ 0x27
#endif

// Define baud rate
#define __BAUD_SERIAL__ 115200

#endif
