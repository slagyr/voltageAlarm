#ifndef VOLTAGEALARM_LINKEDSWITCH_H
#define VOLTAGEALARM_LINKEDSWITCH_H

#include "Switch.h"


class LinkedSwitch : public Switch {
public:
    LinkedSwitch(Hardware *hardware, uint8_t pin);

    LinkedSwitch(Hardware *hardware, uint8_t pin, bool pullUp);

    void setNext(Switch *next);

    void setup() override;

    bool hasNext();

    void on() override;

    void off() override;

private:
    Switch *next = nullptr;
};


#endif //VOLTAGEALARM_LINKEDSWITCH_H
