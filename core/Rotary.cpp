
#include "Rotary.h"


Rotary::Rotary(Hardware *hardware, uint8_t sw, uint8_t dt, uint8_t clk) {
    this->hardware = hardware;
    this->sw = sw;
    this->dt = dt;
    this->clk = clk;
    position = 0;
    updated = true;
    debounceDelay = 50;
    lastEventTime = 0;
}

void Rotary::setup() const {
    hardware->pinToInput(sw);
    hardware->pinToInput(dt);
    hardware->pinToInput(clk);
    hardware->setPinHigh(sw);
}

Hardware *Rotary::getHardware() {
    return hardware;
}

int Rotary::getPosition() {
    return position;
}

int Rotary::getSW() {
    return sw;
}

int Rotary::getDT() {
    return dt;
}

int Rotary::getCLK() {
    return clk;
}

bool Rotary::hasUpdate() {
    return updated;
}

void Rotary::rest() {
    updated = false;
    clicked = false;
}

void Rotary::handleRotation() {
    if (notBounced()) {
        int clkValue = hardware->readDigitalPin(clk);
        int dtValue = hardware->readDigitalPin(dt);
        position += clkValue == dtValue ? 1 : - 1;
        updated = true;
    }
}

int Rotary::getDebounceDelay() {
    return debounceDelay;
}

void Rotary::setDebouceDelay(int delay) {
    debounceDelay = delay;
}

bool Rotary::notBounced() {
    unsigned long now = hardware->getMillis();
    if (now > lastEventTime + debounceDelay) {
        lastEventTime = now;
        return true;
    } else
        return false;
}

void Rotary::handleClick() {
    if (notBounced()) {
        clicked = true;
        updated = true;
    }
}

bool Rotary::wasClicked() {
    return clicked;
}

void Rotary::setPosition(int position) {
    this->position = position;
    updated = true;
}

void Rotary::setClicked(bool b) {
    clicked = b;
    updated = true;
}
