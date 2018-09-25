#ifndef MOCKHARDWARE_H
#define MOCKHARDWARE_H

#include <Hardware.h>
#include <queue>
#include <string>
using namespace std;

class MockHardware : public Hardware {

public:

    void pinToInput(uint8_t pin) override;

    int digitalRead(uint8_t pin) override;

    unsigned long getMillis() override;

    string pins[99];
    queue<int> pinReads[99] ;
    queue<unsigned int> millisReads;
};


#endif //MOCKHARDWARE_H
