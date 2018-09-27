#ifndef VOLTAGEALARM_MOCKMUSIC_H
#define VOLTAGEALARM_MOCKMUSIC_H

#include <Music.h>

class MockMusic : public Music {
public:
    MockMusic(Hardware* hardware, uint8_t pin) : Music(hardware, pin) {}

    void play() override {
        Music::play();
        timesPlayed++;
    }

    int timesPlayed = 0;
};

#endif //VOLTAGEALARM_MOCKMUSIC_H
