#ifndef MOCKVOLTAGESENSOR_H
#define MOCKVOLTAGESENSOR_H

#include "VoltageSensor.h"

class MockVoltageSensor : public VoltageSensor {
public:
    MockVoltageSensor() : VoltageSensor(nullptr, 0, 0.0) {
    }

    double readVoltage() override {
        return volts;
    }

    double volts = 5.0;
};

#endif
