#ifndef VOLTAGEALARM_SWITCH_H
#define VOLTAGEALARM_SWITCH_H


#include "Hardware.h"

class Switch {

public:
    Switch(Hardware *hardware, uint8_t pin);

    void setup();
    uint8_t getPin() const;
    void on();
    void off();
    bool isOn();

private:

    bool currentlyOn;
    Hardware *hardware;
    uint8_t pin;
};


#endif //VOLTAGEALARM_SWITCH_H
