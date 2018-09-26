#ifndef VOLTAGESENSOR_H
#define VOLTAGESENSOR_H

#include "Hardware.h"

class VoltageSensor {

public:

    VoltageSensor(Hardware *hardware, uint8_t pin, double inteferenceAdjustment);
    virtual double readVoltage();
    Hardware* getHardware();
    uint8_t getPin();

    uint8_t pin;
    Hardware *hardware;

    void setInterferenceAdjustment(double error);
    double getInterferenceAdjustment();

    double interferenceAdjustment = 0;
};

#endif
