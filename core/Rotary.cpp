
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
    lastClickTime = 0;
    minClickSeparation = 1000;
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
    if (notBounced(hardware->getMillis())) {
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

bool Rotary::notBounced(unsigned long now) {
    if (now > lastEventTime + debounceDelay) {
        lastEventTime = now;
        return true;
    } else
        return false;
}

void Rotary::handleClick() {
    unsigned long now = hardware->getMillis();
    if (notBounced(now)) {
        if(now > lastClickTime + minClickSeparation) {
            clicked = true;
            updated = true;
            lastClickTime = now;
        }
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

unsigned int Rotary::getMinClickSeparation() const {
    return minClickSeparation;
}

void Rotary::setMinClickSeparation(unsigned int minClickSeparation) {
    Rotary::minClickSeparation = minClickSeparation;
}
