#include <gtest/gtest.h>
#include "Music.h"
#include "MockHardware.h"

class MusicTest : public ::testing::Test {
protected:

    MockHardware *hardware;
    Music *music;

    virtual void SetUp() {
        hardware = new MockHardware();
        music = new Music(hardware, 6);
        music->setup();
    }

    virtual void TearDown() {
        delete music;
        delete hardware;
    }
};

TEST_F(MusicTest, CreationWithPins) {
    EXPECT_EQ(hardware, music->getHardware());
    EXPECT_EQ(6, music->getPin());
}

TEST_F(MusicTest, Setup) {
    EXPECT_EQ("OUTPUT", hardware->pinModes[6]);
}

TEST_F(MusicTest, AddingNotes) {
    EXPECT_EQ(0, music->countNotes());

    music->addNote(NOTE_C5, WHOLE_NOTE);

    EXPECT_EQ(1, music->countNotes());

    auto note = music->getNote(0);
    EXPECT_EQ(NOTE_C5, note->frequency);
    EXPECT_EQ(600, note->duration);
}

TEST_F(MusicTest, NoteDurations) {
    EXPECT_EQ(1200, music->getNoteDuration(DOUBLE_NOTE));
    EXPECT_EQ(600, music->getNoteDuration(WHOLE_NOTE));
    EXPECT_EQ(525, music->getNoteDuration(SEVEN_EIGHTHS_NOTE));
    EXPECT_EQ(450, music->getNoteDuration(THREE_QUARTERS_NOTE));
    EXPECT_EQ(375, music->getNoteDuration(FIVE_EIGHTHS_NOTE));
    EXPECT_EQ(300, music->getNoteDuration(HALF_NOTE));
    EXPECT_EQ(225, music->getNoteDuration(THREE_EIGHTHS_NOTE));
    EXPECT_EQ(150, music->getNoteDuration(QUARTER_NOTE));
    EXPECT_EQ(75, music->getNoteDuration(EIGHTH_NOTE));
    EXPECT_EQ(37, music->getNoteDuration(SIXTEENTH_NOTE));

    music->setWholeNoteDuration(800);

    EXPECT_EQ(1600, music->getNoteDuration(DOUBLE_NOTE));
    EXPECT_EQ(800, music->getNoteDuration(WHOLE_NOTE));
    EXPECT_EQ(700, music->getNoteDuration(SEVEN_EIGHTHS_NOTE));
    EXPECT_EQ(600, music->getNoteDuration(THREE_QUARTERS_NOTE));
    EXPECT_EQ(500, music->getNoteDuration(FIVE_EIGHTHS_NOTE));
    EXPECT_EQ(400, music->getNoteDuration(HALF_NOTE));
    EXPECT_EQ(300, music->getNoteDuration(THREE_EIGHTHS_NOTE));
    EXPECT_EQ(200, music->getNoteDuration(QUARTER_NOTE));
    EXPECT_EQ(100, music->getNoteDuration(EIGHTH_NOTE));
    EXPECT_EQ(50, music->getNoteDuration(SIXTEENTH_NOTE));
}

TEST_F(MusicTest, PauseBetweenNotes) {
    EXPECT_EQ(10, music->getPauseBetweenNotes());

    music->setPauseBetweenNotes(5);

    EXPECT_EQ(5, music->getPauseBetweenNotes());
}

TEST_F(MusicTest, NoCrashOnEmptyNotes) {
    music->play();
    EXPECT_EQ(0, hardware->notesPlayed.size());
}

TEST_F(MusicTest, PlaySimpleSong) {
    music->addNote(NOTE_C5, WHOLE_NOTE);
    music->addNote(NOTE_G5, HALF_NOTE);

    EXPECT_EQ(0, hardware->notesPlayed.size());
    music->play();
    EXPECT_EQ(1, hardware->notesPlayed.size());
    EXPECT_EQ(NOTE_C5, hardware->notesPlayed[0]->frequency);
    EXPECT_EQ(590, hardware->notesPlayed[0]->duration);
    hardware->notesPlayed.clear();

    hardware->millisReads.push(300);
    music->play();
    EXPECT_EQ(0, hardware->notesPlayed.size());

    hardware->millisReads.push(600);
    music->play();
    EXPECT_EQ(1, hardware->notesPlayed.size());
    EXPECT_EQ(NOTE_G5, hardware->notesPlayed[0]->frequency);
    EXPECT_EQ(290, hardware->notesPlayed[0]->duration);
    hardware->notesPlayed.clear();

    hardware->millisReads.push(900);
    music->play();
    EXPECT_EQ(0, hardware->notesPlayed.size());
}

TEST_F(MusicTest, LoopingValues) {
    EXPECT_EQ(false, music->isLoop());
    EXPECT_EQ(1000, music->getLoopDelay());

    music->setLoop(true);
    music->setLoopDelay(4321);

    EXPECT_EQ(true, music->isLoop());
    EXPECT_EQ(4321, music->getLoopDelay());
}

TEST_F(MusicTest, NotLooping) {
    music->addNote(NOTE_C5, WHOLE_NOTE);
    music->setLoop(false);
    for(int i = 0; i < 6001; i += 100) {
        hardware->millisReads.push(i);
        music->play();
    }
    EXPECT_EQ(1, hardware->notesPlayed.size());
}

TEST_F(MusicTest, Looping) {
    music->addNote(NOTE_C5, WHOLE_NOTE);
    music->setLoop(true);
    music->setLoopDelay(600);
    for(int i = 0; i < 6000; i += 100) {
        hardware->millisReads.push(i);
        music->play();
    }
    EXPECT_EQ(5, hardware->notesPlayed.size());
}
