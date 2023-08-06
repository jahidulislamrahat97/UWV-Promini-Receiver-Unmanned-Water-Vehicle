#include "UWV.h"

UWV::UWV()
{
    this->rudderPin = RUDDER_PIN;
    this->escPin = ESC_PIN;
    this->escPowerPin = ESC_POWER_PIN;
    this->maxPulseLength = MAX_PULSE_LENGTH;
    this->minPulseLength = MIN_PULSE_LENGTH;
    this->maxUwvSpeed = MAX_UWV_SPEED;
    this->minUwvSpeed = MIN_UWV_SPEED;
    this->maxRudderAngleLeft = MAX_RUDDER_ANGLE_LEFT;
    this->maxRudderAngleRight = MAX_RUDDER_ANGLE_RIGHT;
    this->rudderAngleCenter = RUDDER_ANGLE_CENTER;
}
UWV::UWV(const int rudderPin, const int escPin, const int escPowerPin, int minPulseLength, int maxPulseLength, int minUwvSpeed, int maxUwvSpeed)
{
    this->rudderPin = rudderPin;
    this->escPin = escPin;
    this->escPowerPin = escPowerPin;
    this->maxPulseLength = maxPulseLength;
    this->minPulseLength = minPulseLength;
    this->maxUwvSpeed = maxUwvSpeed;
    this->minUwvSpeed = minUwvSpeed;
}

void UWV::init()
{
    if (DEBUG)
        Serial.println("UWV initialized.");

    rudder.attach(rudderPin);
    esc.attach(escPin, minPulseLength, maxPulseLength);
    pinMode(escPowerPin, OUTPUT);
    escDisarm();
}

void UWV::escDisarm()
{
    if (DEBUG)
        Serial.println("UWV Disarm");

    esc.writeMicroseconds(minPulseLength);
    digitalWrite(escPowerPin, HIGH);
    arm = false;
}

void UWV::escArm()
{
    if (DEBUG)
        Serial.println("UWV Arm");

    esc.writeMicroseconds(minPulseLength);
    digitalWrite(escPowerPin, LOW);
    arm = true;
}

void UWV::setSpeed(int speed)
{
    if (arm)
    {
        int value = map(speed, 0, 255, minPulseLength, maxPulseLength);
        esc.writeMicroseconds(value);
        if (DEBUG)
        {
            Serial.print("ESC PWM Write: ");
            Serial.println(value);
        }
    }
    else
    {
        if (DEBUG)
        {
            Serial.println("UWB Not Armed");
        }
    }
}

void UWV::setRudder(int angle)
{
    if (angle > maxRudderAngleLeft)
    {
        rudder.write(maxRudderAngleLeft);
        if (DEBUG)
            Serial.println("rudder write: maxRudderAngleLeft");
    }
    else if (angle < maxRudderAngleRight)
    {
        rudder.write(maxRudderAngleRight);
        if (DEBUG)
            Serial.println("rudder write: maxRudderAngleRight");
    }
    else
    {
        rudder.write(angle);
        if (DEBUG)
            Serial.print("rudder write: ");
            Serial.println(angle);
    }
}