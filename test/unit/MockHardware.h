#ifndef MOCKHARDWARE_H
#define MOCKHARDWARE_H

#include <Hardware.h>
#include <queue>
#include <string>
#include <Music.h>
#include <iostream>

using namespace std;

class PlayedNote {
public:

    uint8_t pin;
    unsigned int frequency;
    unsigned long duration;

    PlayedNote(uint8_t pin, unsigned int frequency, unsigned long duration) {
        this->pin = pin;
        this->frequency = frequency;
        this->duration = duration;
    }
};

class MockHardware : public Hardware {

public:

    string pinModes[40];
    queue<int> digitalReads[40];
    queue<int> analogReads[20];
    queue<unsigned int> millisReads;
    string digitalWrites[40];
    vector<PlayedNote *> notesPlayed;
    vector<unsigned long> delays;

    void pinToInput(uint8_t pin) override { pinModes[pin] = "INPUT"; }

    void pinToOutput(uint8_t pin) override { pinModes[pin] = "OUTPUT"; }

    int readDigitalPin(uint8_t pin) override {
        if (digitalReads[pin].empty())
            return -1;
        else {
            int value = digitalReads[pin].front();
            digitalReads[pin].pop();
            return value;
        }
    }

    int readAnalogPin(uint8_t pin) override {
        if (analogReads[pin].empty())
            return -1;
        else {
            int value = analogReads[pin].front();
            analogReads[pin].pop();
            return value;
        }
    }

    unsigned long getMillis() override {
        if (millisReads.empty())
            return 0;
        else {
            int value = millisReads.front();
            millisReads.pop();
            return value;
        }
    }

    void print(const char *value) override { cout << value; }

    void print(int value) override { cout << value; }

    void setPinHigh(uint8_t pin) override { digitalWrites[pin] = "HIGH"; }

    void setPinLow(uint8_t pin) override { digitalWrites[pin] = "LOW"; }

    void playNote(uint8_t pin, unsigned int frequency, unsigned long duration) override {
        notesPlayed.push_back(new PlayedNote(pin, frequency, duration));
    }

    void sleep(unsigned long duration) override { delays.push_back(duration); }
};

#endif
