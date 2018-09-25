#include "MockHardware.h"
#include <iostream>

void MockHardware::pinToInput(uint8_t pin) {
    pinModes[pin] = "INPUT";
}

void MockHardware::pinToOutput(uint8_t pin) {
    pinModes[pin] = "OUTPUT";
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

void MockHardware::playNote(uint8_t pin, unsigned int frequency, unsigned long duration) {
    notesPlayed.push_back(new PlayedNote(pin, frequency, duration));
}

PlayedNote::PlayedNote(uint8_t pin, unsigned int frequency, unsigned long duration) {
    this->pin = pin;
    this->frequency = frequency;
    this->duration = duration;
}
