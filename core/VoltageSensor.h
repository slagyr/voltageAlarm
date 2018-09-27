#ifndef VOLTAGESENSOR_H
#define VOLTAGESENSOR_H

#include "Hardware.h"

class VoltageSensor {

public:

    VoltageSensor(Hardware *hardware, uint8_t pin);
    virtual float readVoltage();
    Hardware* getHardware();
    uint8_t getPin();
    void setInterferenceAdjustment(float error);
    float getInterferenceAdjustment();

private:
    uint8_t pin;
    Hardware *hardware;
    float interferenceAdjustment = 0;
};

#endif
