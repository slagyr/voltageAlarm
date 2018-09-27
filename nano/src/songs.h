#ifndef NANO_SONGS_H
#define NANO_SONGS_H

#include "Music.h"

void hereComesTheSun(Music *music) {
    music->setWholeNoteDuration(2000);
    music->setLoop(true);
    music->setLoopDelay(music->getNoteDuration(WHOLE_NOTE));

    music->addNote(NOTE_B5, EIGHTH_NOTE);
    music->addNote(NOTE_A5, QUARTER_NOTE);
    music->addNote(NOTE_B5, QUARTER_NOTE);

    music->addNote(NOTE_G5, HALF_NOTE);
    music->addNote(NOTE_B5, EIGHTH_NOTE);
    music->addNote(NOTE_G5, EIGHTH_NOTE);
    music->addNote(NOTE_A5, EIGHTH_NOTE);
    music->addNote(NOTE_B5, THREE_EIGHTHS_NOTE);

//    music->addNote(NOTE_REST, EIGHTH_NOTE);
//    music->addNote(NOTE_B5, EIGHTH_NOTE);
//    music->addNote(NOTE_A5, QUARTER_NOTE);
//    music->addNote(NOTE_B5, QUARTER_NOTE);
//
//    music->addNote(NOTE_G5, HALF_NOTE);
//    music->addNote(NOTE_B5, EIGHTH_NOTE);
//    music->addNote(NOTE_A5, QUARTER_NOTE);
//    music->addNote(NOTE_G5, THREE_EIGHTHS_NOTE);
//
//    music->addNote(NOTE_REST, EIGHTH_NOTE);
//    music->addNote(NOTE_B5, QUARTER_NOTE);
//    music->addNote(NOTE_A5, QUARTER_NOTE);
//    music->addNote(NOTE_G5, QUARTER_NOTE);
//
//    music->addNote(NOTE_E6, EIGHTH_NOTE);
//    music->addNote(NOTE_G6, EIGHTH_NOTE);
//    music->addNote(NOTE_A6, EIGHTH_NOTE);
//    music->addNote(NOTE_D6, EIGHTH_NOTE);
//    music->addNote(NOTE_G6, EIGHTH_NOTE);
//    music->addNote(NOTE_A6, EIGHTH_NOTE);
//    music->addNote(NOTE_C6, EIGHTH_NOTE);
//    music->addNote(NOTE_G6, EIGHTH_NOTE);
//
//    music->addNote(NOTE_A6, EIGHTH_NOTE);
//    music->addNote(NOTE_D6, EIGHTH_NOTE);
//    music->addNote(NOTE_G6, EIGHTH_NOTE);
//    music->addNote(NOTE_A6, EIGHTH_NOTE);
//    music->addNote(NOTE_G6, EIGHTH_NOTE);
//    music->addNote(NOTE_FS6, EIGHTH_NOTE);
//    music->addNote(NOTE_E6, EIGHTH_NOTE);
//    music->addNote(NOTE_D6, EIGHTH_NOTE);
//
//    music->addNote(NOTE_G6, QUARTER_NOTE);
}

void aobtd(Music *music) {
    music->addNote(NOTE_E4, EIGHTH_NOTE);
    music->addNote(NOTE_E4, EIGHTH_NOTE);
    music->addNote(NOTE_G4, EIGHTH_NOTE);
    music->addNote(NOTE_E4, SIXTEENTH_NOTE);
    music->addNote(NOTE_A4, EIGHTH_NOTE);
//    music->addNote(NOTE_REST, SIXTEENTH_NOTE);
//    music->addNote(NOTE_REST, EIGHTH_NOTE);
}

void bbb(Music *music) {
    music->addNote(NOTE_REST, QUARTER_NOTE);
    music->addNote(NOTE_E4, EIGHTH_NOTE);
    music->addNote(NOTE_REST, EIGHTH_NOTE);
    music->addNote(NOTE_E4, EIGHTH_NOTE);
    music->addNote(NOTE_REST, EIGHTH_NOTE);
    music->addNote(NOTE_E4, EIGHTH_NOTE);
    music->addNote(NOTE_REST, THREE_EIGHTHS_NOTE);
}

void anotherOneBitesTheDust(Music *music) {
    music->setWholeNoteDuration(2000);
    music->setLoop(true);
    music->setLoopDelay(2000);

    bbb(music);
    aobtd(music);
//    bbb(music);
//    aobtd(music);
//    music->addNote(NOTE_B4, QUARTER_NOTE);
//    music->addNote(NOTE_B4, SIXTEENTH_NOTE);
//    music->addNote(NOTE_AS4, SIXTEENTH_NOTE);
//    music->addNote(NOTE_A4, SIXTEENTH_NOTE);
//    music->addNote(NOTE_G4, EIGHTH_NOTE);
//    music->addNote(NOTE_E4, EIGHTH_NOTE);
//
//    music->addNote(NOTE_B4, SIXTEENTH_NOTE);
//    music->addNote(NOTE_B4, SIXTEENTH_NOTE);
//    music->addNote(NOTE_AS4, SIXTEENTH_NOTE);
//    music->addNote(NOTE_A4, SIXTEENTH_NOTE);
//    music->addNote(NOTE_G4, EIGHTH_NOTE);
//    music->addNote(NOTE_E4, QUARTER_NOTE);
//
//    aobtd(music);
}

#endif //NANO_SONGS_H
