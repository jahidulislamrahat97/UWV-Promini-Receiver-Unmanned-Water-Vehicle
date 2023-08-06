#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG                           1
#define CODE_UPLOAD                     1
#define SERIAL_BAUDRATE                 9600
#define NRF_ID                          "2209110000"
#define MIN_PULSE_LENGTH                1000 // Minimum pulse length in µs for ESC
#define MAX_PULSE_LENGTH                2000 // Maximum pulse length in µs for ESC
#define MAX_RUDDER_ANGLE_LEFT           120
#define MAX_RUDDER_ANGLE_RIGHT          90
#define RUDDER_ANGLE_CENTER             105
#define MIN_UWV_SPEED                   12
#define MAX_UWV_SPEED                   35


#define CE_PIN                          10
#define CSN_PIN                         9
#define A9G_TX                          6
#define A9G_RX                          7
#define ESC_PIN                         5
#define ESC_POWER_PIN                   2
#define RUDDER_PIN                      9
#define INDICATOR_RGB_LED_PIN           10

#endif // !CONFIG_H