#include "LinkedSwitch.h"

LinkedSwitch::LinkedSwitch(Hardware *hardware, uint8_t pin) : Switch(hardware, pin) {}

LinkedSwitch::LinkedSwitch(Hardware *hardware, uint8_t pin, bool pullUp) : Switch(hardware, pin, pullUp) {}

void LinkedSwitch::setNext(Switch *next) {
    this->next = next;
}

void LinkedSwitch::setup() {
    Switch::setup();
    if(hasNext())
        next->setup();
}

bool LinkedSwitch::hasNext() {
    return next != nullptr;
}

void LinkedSwitch::on() {
    Switch::on();
    if(hasNext())
        next->on();
}

void LinkedSwitch::off() {
    Switch::off();
    if(hasNext())
        next->off();
}



