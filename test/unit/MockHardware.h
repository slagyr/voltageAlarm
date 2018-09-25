#ifndef MOCKHARDWARE_H
#define MOCKHARDWARE_H

#include <Hardware.h>
#include <queue>
#include <string>
#include <Music.h>

using namespace std;

class PlayedNote {
public:
    PlayedNote(uint8_t pin, unsigned int frequency, unsigned long duration);
    uint8_t pin;
    unsigned int frequency;
    unsigned long duration;
};

class MockHardware : public Hardware {

public:

    void pinToInput(uint8_t pin) override;
    void pinToOutput(uint8_t pin) override;
    int readDigitalPin(uint8_t pin) override;
    unsigned long getMillis() override;
    void print(const char *value) override;
    void print(int value) override;
    void setPinHigh(uint8_t pin) override;
    void setPinLow(uint8_t pin) override;

    void playNote(uint8_t pin, unsigned int frequency, unsigned long duration) override;

    string pinModes[99];
    queue<int> pinReads[99] ;
    queue<unsigned int> millisReads;
    string digitalWrites[99];
    vector<PlayedNote*> notesPlayed;
};


#endif //MOCKHARDWARE_H
