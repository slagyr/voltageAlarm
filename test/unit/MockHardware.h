#ifndef MOCKHARDWARE_H
#define MOCKHARDWARE_H

#include <Hardware.h>
#include <queue>
#include <string>
using namespace std;

class MockHardware : public Hardware {

public:

    void pinToInput(uint8_t pin) override;
    int readDigitalPin(uint8_t pin) override;
    unsigned long getMillis() override;
    void print(const char *value) override;
    void print(int value) override;

    void setPinHigh(uint8_t pin) override;

    void setPinLow(uint8_t pin) override;

    string pinModes[99];
    queue<int> pinReads[99] ;
    queue<unsigned int> millisReads;
    string digitalWrites[99];
};


#endif //MOCKHARDWARE_H
