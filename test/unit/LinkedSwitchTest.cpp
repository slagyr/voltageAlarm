#include <gtest/gtest.h>
#include "MockHardware.h"
#include "LinkedSwitch.h"
#include "Switch.h"

class LinkedSwitchTest : public ::testing::Test {
protected:

    MockHardware *hardware;
    LinkedSwitch *rootSwitch;
    Switch *childSwitch;

    virtual void SetUp() {
        hardware = new MockHardware();
        rootSwitch = new LinkedSwitch(hardware, 1);
        childSwitch = new Switch(hardware, 2);
        rootSwitch->setNext(childSwitch);
    }

    virtual void TearDown() {
        delete rootSwitch;
        delete childSwitch;
        delete hardware;
    }
};

TEST_F(LinkedSwitchTest, SetupWithoutNext) {
    rootSwitch->setup();
    EXPECT_EQ(hardware, rootSwitch->getHardware());
    EXPECT_EQ(1, rootSwitch->getPin());
    EXPECT_EQ("OUTPUT", hardware->pinModes[1]);
}

TEST_F(LinkedSwitchTest, SetupWithNext) {
    rootSwitch->setNext(childSwitch);
    rootSwitch->setup();
    EXPECT_EQ(hardware, rootSwitch->getHardware());
    EXPECT_EQ(1, rootSwitch->getPin());
    EXPECT_EQ("OUTPUT", hardware->pinModes[1]);

    EXPECT_EQ(hardware, childSwitch->getHardware());
    EXPECT_EQ(2, childSwitch->getPin());
    EXPECT_EQ("OUTPUT", hardware->pinModes[2]);
}

TEST_F(LinkedSwitchTest, On) {
    rootSwitch->setNext(childSwitch);
    rootSwitch->setup();
    rootSwitch->on();

    EXPECT_EQ(true, rootSwitch->isOn());
    EXPECT_EQ(true, childSwitch->isOn());
}

TEST_F(LinkedSwitchTest, Off) {
    rootSwitch->setNext(childSwitch);
    rootSwitch->setup();
    rootSwitch->on();
    rootSwitch->off();

    EXPECT_EQ(false, rootSwitch->isOn());
    EXPECT_EQ(false, childSwitch->isOn());
}
