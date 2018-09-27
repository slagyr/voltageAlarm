#include "Music.h"

Note::Note(unsigned short frequency, unsigned short duration) {
    this->frequency = frequency;
    this->duration = duration;
}

bool Note::operator==(const Note &other) const {
    return frequency == other.frequency && duration == other.duration;
}

Music::Music(Hardware *hardware, uint8_t pin) {
    this->hardware = hardware;
    this->pin = pin;
    pauseBetweenNotes = 10;
    nextNote = 0;
    finishTime = 0;
    loop = false;
    loopDelay = 1000;
}

void Music::setup() {
    hardware->pinToOutput(pin);
    setWholeNoteDuration(2000);
}

Hardware *Music::getHardware() {
    return hardware;
}

uint8_t Music::getPin() {
    return pin;
}

void Music::addNote(unsigned short frequency, unsigned short duration) {
    if (duration < 10)
        duration = this->duration(duration);
    notes.add(new Note(frequency, duration));
}

unsigned short Music::duration(unsigned short i) const {
    switch (i) {
        case DOUBLE_NOTE :
            return wholeNoteDuration * 2;
        case WHOLE_NOTE :
            return wholeNoteDuration;
        case SEVEN_EIGHTHS_NOTE :
            return wholeNoteDuration * 7 / 8;
        case THREE_QUARTERS_NOTE :
            return wholeNoteDuration * 3 / 4;
        case FIVE_EIGHTHS_NOTE :
            return wholeNoteDuration * 5 / 8;
        case HALF_NOTE :
            return wholeNoteDuration / 2;
        case THREE_EIGHTHS_NOTE :
            return wholeNoteDuration * 3 / 8;
        case QUARTER_NOTE :
            return wholeNoteDuration / 4;
        case EIGHTH_NOTE :
            return wholeNoteDuration / 8;
        case SIXTEENTH_NOTE :
            return wholeNoteDuration / 16;
        default :
            return i;
    }
}

int Music::countNotes() {
    return notes.size();
}

Note *Music::getNote(unsigned short index) {
    return notes.get(index);
}

void Music::setWholeNoteDuration(unsigned short duration) {
    wholeNoteDuration = duration;
}

unsigned short Music::getNoteDuration(unsigned short index) {
    return duration(index);
}

unsigned short Music::getPauseBetweenNotes() {
    return pauseBetweenNotes;
}

void Music::setPauseBetweenNotes(unsigned short duration) {
    pauseBetweenNotes = duration;
}

void Music::play() {
    int noteCount = notes.size();
    if (nextNote < noteCount) {
        Note *note = notes.get(nextNote);
        unsigned long now = hardware->getMillis();
        if (now >= finishTime) {
            nextNote++;
            finishTime = now + note->duration;
            if (loop && nextNote >= noteCount) {
                nextNote = 0;
                finishTime += loopDelay;
            }
            if (note->frequency >= 31) // otherwise a rest
                hardware->playNote(pin, note->frequency, note->duration - pauseBetweenNotes);
        }
    }
}

bool Music::isLoop() {
    return loop;
}

void Music::setLoop(bool b) {
    loop = b;
}

unsigned short Music::getLoopDelay() {
    return loopDelay;
}

void Music::setLoopDelay(unsigned short duration) {
    loopDelay = duration;
}
