#include "Music.h"

Note::Note(unsigned int frequency, unsigned long duration) {
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

void Music::addNote(unsigned int frequency, unsigned long duration) {
    if(duration < 10)
        duration = durations[duration];
    notes.add(new Note(frequency, duration));
}

int Music::countNotes() {
    return notes.size();
}

Note *Music::getNote(int index) {
    return notes.get(index);
}

void Music::setWholeNoteDuration(unsigned long duration) {
    durations[DOUBLE_NOTE] = duration * 2;
    durations[WHOLE_NOTE] = duration;
    durations[SEVEN_EIGHTHS_NOTE] = duration * 7 / 8;
    durations[THREE_QUARTERS_NOTE] = duration * 3 / 4;
    durations[FIVE_EIGHTHS_NOTE] = duration * 5 / 8;
    durations[HALF_NOTE] = duration / 2;
    durations[THREE_EIGHTHS_NOTE] = duration * 3 / 8;
    durations[QUARTER_NOTE] = duration / 4;
    durations[EIGHTH_NOTE] = duration / 8;
    durations[SIXTEENTH_NOTE] = duration / 16;
}

unsigned long Music::getNoteDuration(int index) {
    return durations[index];
}

unsigned long Music::getPauseBetweenNotes() {
    return pauseBetweenNotes;
}

void Music::setPauseBetweenNotes(unsigned long duration) {
    pauseBetweenNotes = duration;
}

void Music::play() {
    int noteCount = notes.size();
    if(nextNote < noteCount) {
        Note *note = notes.get(nextNote);
        unsigned long now = hardware->getMillis();
        if(now >= finishTime)
        {
            nextNote++;
            finishTime = now + note->duration;
            if(loop && nextNote >= noteCount) {
                nextNote = 0;
                finishTime += loopDelay;
            }
            if(note->frequency >= 31) // otherwise a rest
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

unsigned long Music::getLoopDelay() {
    return loopDelay;
}

void Music::setLoopDelay(unsigned long duration) {
    loopDelay = duration;
}
