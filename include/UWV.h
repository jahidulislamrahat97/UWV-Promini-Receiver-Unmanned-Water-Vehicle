#ifndef UWV_H
#define UWV_H
#include <Arduino.h>
#include <Servo.h>
#include "Config.h"

class UWV
{
    private:
        Servo rudder, esc;
        int rudderPin;
        int escPin;
        int escPowerPin;
        int minPulseLength;
        int maxPulseLength;
        int minUwvSpeed;
        int maxUwvSpeed;
        int maxRudderAngleLeft;
        int maxRudderAngleRight;
        int rudderAngleCenter;



    public:
        bool arm = false;
        bool remoteSate = true;
        UWV();
        UWV(int rudderPin, int escPin, int escPowerPin, int minPulseLength, int maxPulseLength, int minUwvSpeed, int maxUwvSpeed);
        void init();
        void escDisarm();
        void escArm();
        void setSpeed(int speed);
        void setRudder(int angle);
};

#endif