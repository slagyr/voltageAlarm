#include "MockHardware.h"
#include <iostream>

void MockHardware::pinToInput(uint8_t pin) {
    pinModes[pin] = "INPUT";
}

int MockHardware::readDigitalPin(uint8_t pin) {
    if (pinReads[pin].empty())
        return -1;
    else {
        int value = pinReads[pin].front();
        pinReads[pin].pop();
        return value;
    }
}

unsigned long MockHardware::getMillis() {
    if (millisReads.empty())
        return 0;
    else {
        int value = millisReads.front();
        millisReads.pop();
        return value;
    }
}

void MockHardware::print(const char *value) {
    cout << value;
}

void MockHardware::print(int value) {
    cout << value;
}

void MockHardware::setPinHigh(uint8_t pin) {
    digitalWrites[pin] = "HIGH";
}

void MockHardware::setPinLow(uint8_t pin) {
    digitalWrites[pin] = "LOW";
}
