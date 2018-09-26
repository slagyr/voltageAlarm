#include <gtest/gtest.h>
#include "Controller.h"
#include "MockVoltageSensor.h"
#include "MockDisplay.h"
#include "MockHardware.h"

class ControllerTest : public ::testing::Test {
protected:

    Controller *controller;
    MockVoltageSensor *loadPositive;
    MockVoltageSensor *loadNegative;
    MockDisplay *display;
    MockHardware *hardware;


    virtual void SetUp() {
        hardware = new MockHardware();
        loadPositive = new MockVoltageSensor();
        loadNegative = new MockVoltageSensor();
        display = new MockDisplay();
        controller = new Controller(hardware, loadPositive, loadNegative, display);
    }

    virtual void TearDown() {
        delete display;
        delete hardware;
        delete loadPositive;
        delete loadNegative;
        delete controller;
    }
};

TEST_F(ControllerTest, AllTheThings_InTheContructor) {
    EXPECT_EQ(hardware, controller->getHardware());
    EXPECT_EQ(loadPositive, controller->getLoadPositive());
    EXPECT_EQ(loadNegative, controller->getLoadNegative());
    EXPECT_EQ(display, controller->getDisplay());
}

TEST_F(ControllerTest, DefaultValues) {
    EXPECT_DOUBLE_EQ(5.0, controller->getCutoffVoltage());
    EXPECT_EQ(false, controller->isCutoffAbove());
}

TEST_F(ControllerTest, SplashScreen) {
    EXPECT_STREQ("Splash", controller->getScreen()->getName());
    controller->tick(100);
    EXPECT_STREQ("Volt Alarm v1.0", display->line1);
    EXPECT_STREQ("Micah Martin", display->line2);
    EXPECT_EQ(5000, controller->getScreen()->getIdleTimeout());
}

TEST_F(ControllerTest, SplashToHomeAfterTimeout) {
    controller->tick(100);
    EXPECT_STREQ("Splash", controller->getScreen()->getName());
    controller->tick(5001);
    EXPECT_STREQ("Home", controller->getScreen()->getName());
}

TEST_F(ControllerTest, HomeScreenDisplay) {
    loadPositive->volts = 4.198;
    loadNegative->volts = 3.544;
    controller->setCutoffVoltage(2.5);
    controller->setScreen(controller->getHomeScreen());
    controller->tick(9999);
    EXPECT_STREQ("Home", controller->getScreen()->getName());

    EXPECT_STREQ("Voltage: 4.2 3.5", display->line1);
    EXPECT_STREQ("Cutoff: < 2.5", display->line2);
}

