#ifndef VOLTAGESENSOR_H
#define VOLTAGESENSOR_H

#include "Hardware.h"

class VoltageSensor {

public:

    VoltageSensor(Hardware *hardware, uint8_t pin);
    virtual float readVoltage();
    virtual float getLastReading();
    Hardware* getHardware();
    uint8_t getPin();
    void setInterferenceAdjustment(float error);
    float getInterferenceAdjustment();

protected:
    float lastReading = 0;

private:
    uint8_t pin;
    Hardware *hardware;
    float interferenceAdjustment = 0;
};

#endif
