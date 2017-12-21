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

#define __MILLIS_VOLTAGE_OFFSET__ 2500.0
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

// Define timer upload
#define __MILLIS_TIME_UPDATE__ 500
#define __MILLIS_TIME_UPLOAD__ 15000

// Define Blynk App
#define __BLYNK_LCD_PIN__ 0 // V0
#define __BLYNK_LED_PIN__ 1 // V1
#define __BLYNK_LOAD_PIN__ 2 // V2
#define __BLYNK_GRAPH_PIN__ 3 // V3
#define __BLYNK_HISTORY_GRAPH_CURRENT_PIN__ 4 // V4
#define __BLYNK_HISTORY_GRAPH_POWER_PIN__ 5 // V5
#define __BLYNK_HISTORY_GRAPH_ENERGY_PIN__ 6 // V6

// Define ThingSpeak Web Server
#define __THINGSPEAK_DC_FIELD_CURRENT__ 1
#define __THINGSPEAK_DC_FIELD_WORKING__ 2
#define __THINGSPEAK_AC_FIELD_CURRENT__ 3
#define __THINGSPEAK_AC_FIELD_WORKING__ 4

#endif
