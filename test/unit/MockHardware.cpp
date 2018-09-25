#include "MockHardware.h"

void MockHardware::pinToInput(uint8_t pin) {
    pins[pin] = "INPUT";
}

int MockHardware::digitalRead(uint8_t pin) {
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
