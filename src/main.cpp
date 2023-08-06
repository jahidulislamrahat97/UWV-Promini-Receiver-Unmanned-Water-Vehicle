#include <Arduino.h>
#include <printf.h>
#include <SoftwareSerial.h>
#include <string.h>
#include "Config.h"
#include "NRF.h"
#include "UWV.h"

UWV uwv;
RF24 radio(CE_PIN, CSN_PIN);
NRF_Config nrf_config;

int led = 4;

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);
    printf_begin();
    uwv.init();
     pinMode(led,OUTPUT);

    nrf_config.open_writing_pipe = false;
    nrf_config.open_reading_pipe = true;
    vMakeAddress(nrf_config, 0, NRF_ID);
    vNRF_Config(radio, nrf_config, DEBUG);

    if (DEBUG)
        vPrintDebugMessage(radio);
}


void controlUWV(int data)
{
    /*
    Disarm State    = 1000
    Arm State       = 1001
    Remote Mode     = 1002
    Autonomous Mode = 1003
    Speed           = 2000 : 2255
    Direction Angle = 3000 : 3180
    */
    if (data == 1000)
    {
        uwv.escDisarm();
    }
    if (data == 1001)
    {
        uwv.escArm();
    }
    if (data == 1002)
    {
        // remote mode
        uwv.remoteSate = true;
    }
    if (data == 1003)
    {
        // autonomous Mode.
        uwv.remoteSate = false;
    }
    if (2000 >= data && 2255 <= data)
    {
        int speed = map(data, 2000, 2255, 0, 255);
        uwv.setSpeed(speed);
    }
    if (3000 >= data && 3180 <= data)
    {
        int rudderPosition = map(data, 3000, 3180, 0, 180);
        uwv.setSpeed(rudderPosition);
    }
}

void loop()
{

    int data;
    if (radio.available())
    {
        radio.read(&data, sizeof(int));
        if (DEBUG)
        {
            Serial.print(F("data_to_receive: "));
            Serial.println(data);
            digitalWrite(led,HIGH);
            delay(150);
            digitalWrite(led,LOW);
        }

        // if (uwv.remoteSate)
        // {
        //     // remote control
        //     controlUWV(data);
        // }
        // else
        // {
        //     // autonoumous
        //     controlUWV(data);
        // }
    }
}
