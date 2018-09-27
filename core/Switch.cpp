#include "Switch.h"

Switch::Switch(Hardware *hardware, uint8_t pin) {
    this->hardware = hardware;
    this->pin = pin;
    currentlyOn = false;
}

void Switch::setup() {
    hardware->pinToOutput(pin);
}

void Switch::on() {
    hardware->setPinHigh(pin);
    currentlyOn = true;
}

void Switch::off() {
    hardware->setPinLow(pin);
    currentlyOn = false;
}

bool Switch::isOn() {
    return currentlyOn;
}

uint8_t Switch::getPin() const {
    return pin;
}
