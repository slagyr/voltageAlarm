#include <gtest/gtest.h>
#include "Rotary.h"
#include "MockHardware.h"

class RotaryTest : public ::testing::Test {
protected:

    MockHardware *hardware;
    Rotary *rotary;

    virtual void SetUp() {
        hardware = new MockHardware();
        rotary = new Rotary(hardware, 1, 2, 3);
        rotary->setup();
    }

    virtual void TearDown() {
        delete rotary;
        delete hardware;
    }
};

TEST_F(RotaryTest, CreationWithPins) {
    EXPECT_EQ(hardware, rotary->getHardware());
    EXPECT_EQ(0, rotary->getPosition());
    EXPECT_EQ(1, rotary->getSW());
    EXPECT_EQ(2, rotary->getDT());
    EXPECT_EQ(3, rotary->getCLK());
}

TEST_F(RotaryTest, SettingUpPins) {
    EXPECT_EQ("INPUT", hardware->pinModes[1]);
    EXPECT_EQ("INPUT", hardware->pinModes[2]);
    EXPECT_EQ("INPUT", hardware->pinModes[3]);
    EXPECT_EQ("HIGH", hardware->digitalWrites[1]);
}

TEST_F(RotaryTest, UpdateStatus) {
    EXPECT_EQ(true, rotary->hasUpdate());

    rotary->rest();

    EXPECT_EQ(false, rotary->hasUpdate());
}

TEST_F(RotaryTest, HandlesRotationClockwise) {
    rotary->rest();
    hardware->millisReads.push(123);
    hardware->digitalReads[3].push(0);
    hardware->digitalReads[2].push(0);

    rotary->handleRotation();

    EXPECT_EQ(1, rotary->getPosition());
    EXPECT_EQ(true, rotary->hasUpdate());
}

TEST_F(RotaryTest, HandlesRotationCounterClockwise) {
    rotary->rest();
    hardware->millisReads.push(123);
    hardware->digitalReads[3].push(1);
    hardware->digitalReads[2].push(0);

    rotary->handleRotation();

    EXPECT_EQ(-1, rotary->getPosition());
    EXPECT_EQ(true, rotary->hasUpdate());
}

TEST_F(RotaryTest, DebouceDelayValue) {
    EXPECT_EQ(50, rotary->getDebounceDelay());
    rotary->setDebouceDelay(100);
    EXPECT_EQ(100, rotary->getDebounceDelay());
}

TEST_F(RotaryTest, DebouncingWillIngoreRapidRotations) {
    rotary->rest();
    hardware->millisReads.push(10);
    hardware->digitalReads[3].push(1);
    hardware->digitalReads[2].push(0);

    rotary->handleRotation();

    EXPECT_EQ(0, rotary->getPosition());
    EXPECT_EQ(false, rotary->hasUpdate());
}

TEST_F(RotaryTest, HandlesClick) {
    hardware->millisReads.push(2001);

    rotary->handleClick();

    EXPECT_EQ(true, rotary->hasUpdate());
    EXPECT_EQ(true, rotary->wasClicked());

    rotary->rest();
    EXPECT_EQ(false, rotary->wasClicked());
}

TEST_F(RotaryTest, SettingPosition) {
    rotary->rest();
    rotary->setPosition(10);

    EXPECT_EQ(10, rotary->getPosition());
    EXPECT_EQ(true, rotary->hasUpdate());
}

TEST_F(RotaryTest, MinClickSeparation) {
    rotary->setMinClickSeparation(2000);
    hardware->millisReads.push(2001);
    rotary->handleClick();
    EXPECT_EQ(true, rotary->wasClicked());
    rotary->rest();

    hardware->millisReads.push(3001);
    rotary->handleClick();
    EXPECT_EQ(false, rotary->wasClicked());

    hardware->millisReads.push(4002);
    rotary->handleClick();
    EXPECT_EQ(true, rotary->wasClicked());
}

