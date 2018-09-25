#ifndef HARDWARE_H
#define HARDWARE_H


#include <cstdint>

class Hardware {

public:
    virtual void pinToInput(uint8_t pin) = 0;

    virtual int digitalRead(uint8_t pin) = 0;

    virtual unsigned long getMillis() = 0;
};


#endif
