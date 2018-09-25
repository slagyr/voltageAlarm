#ifndef ARDUINOHARDWARE_H
#define ARDUINOHARDWARE_H


#include <Hardware.h>

class ArduinoHardware : public Hardware {

public:
    void pinToInput(uint8_t pin) override;

    int readDigitalPin(uint8_t pin) override;

    unsigned long getMillis() override;

    void setPinHigh(uint8_t pin) override;

    void setPinLow(uint8_t pin) override;

    void print(const char *value) override;

    void print(int value) override;

};


#endif //ARDUINOHARDWARE_H
