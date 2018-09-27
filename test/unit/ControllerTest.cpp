#include <gtest/gtest.h>
#include "Controller.h"
#include "MockVoltageSensor.h"
#include "MockDisplay.h"
#include "MockHardware.h"
#include "Rotary.h"
#include "MockConfig.h"
#include "MockMusic.h"

class ControllerTest : public ::testing::Test {
protected:

    Controller *controller;
    MockVoltageSensor *loadPositive;
    MockVoltageSensor *loadNegative;
    MockDisplay *display;
    MockHardware *hardware;
    Rotary *rotary;
    MockConfig *config;
    MockMusic *warning;
    MockMusic *alarm;
    Switch *load;

    virtual void SetUp() {
        hardware = new MockHardware();
        loadPositive = new MockVoltageSensor();
        loadNegative = new MockVoltageSensor();
        display = new MockDisplay();
        rotary = new Rotary(hardware, 1, 2, 3);
        config = new MockConfig();
        warning = new MockMusic(hardware, 4);
        alarm = new MockMusic(hardware, 5);
        load = new Switch(hardware, 6);
        controller = new Controller(hardware, loadPositive, loadNegative, display, rotary, config, alarm, warning, load);
        controller->setup();
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
    EXPECT_EQ(rotary, controller->getRotary());
    EXPECT_EQ(config, controller->getConfig());
    EXPECT_EQ(alarm, controller->getAlarm());
    EXPECT_EQ(warning, controller->getWarning());
}

TEST_F(ControllerTest, Setup) {
    config->nVoltageInterference = -1.2f;
    config->pVoltageInterference = 3.4f;

    controller->setup();

    EXPECT_NEAR(-1.2, loadNegative->getInterferenceAdjustment(), 0.01);
    EXPECT_NEAR(3.4, loadPositive->getInterferenceAdjustment(), 0.01);
    EXPECT_EQ("OUTPUT", hardware->pinModes[warning->getPin()]);
    EXPECT_EQ("OUTPUT", hardware->pinModes[alarm->getPin()]);
    EXPECT_EQ("OUTPUT", hardware->pinModes[load->getPin()]);
}

TEST_F(ControllerTest, SplashScreen) {
    EXPECT_STREQ("Splash", controller->getScreen()->getName());
    controller->tick(1000);
    EXPECT_STREQ("Volt Alarm v1.0", display->line1);
    EXPECT_STREQ("Micah Martin", display->line2);
    EXPECT_EQ(1000, controller->getScreen()->getIdleTimeout());
}

TEST_F(ControllerTest, SplashToHomeAfterTimeout) {
    EXPECT_STREQ("Splash", controller->getScreen()->getName());
    controller->tick(5001);
    EXPECT_STREQ("Home", controller->getScreen()->getName());
}

TEST_F(ControllerTest, HomeScreenDisplay) {
    loadPositive->volts = 4.198;
    loadNegative->volts = 3.544;
    config->cutoffVoltage = 2.5;
    controller->setScreen(controller->getHomeScreen());
    rotary->rest();
    controller->tick(9999);
    EXPECT_STREQ("Home", controller->getScreen()->getName());

    EXPECT_STREQ("Voltage: 4.2 3.5", display->line1);
    EXPECT_STREQ("Cutoff: <2.5 MON", display->line2);
}

TEST_F(ControllerTest, EnteringMenu) {
    controller->setScreen(controller->getHomeScreen());
    rotary->setClicked(true);

    controller->tick(1234);

    Screen *screen = controller->getScreen();
    EXPECT_STREQ("Main Menu", screen->getName());
    EXPECT_EQ(5000, screen->getIdleTimeout());

    EXPECT_STREQ("1 Set Cutoff V  ", display->line1);
    EXPECT_STREQ("2 Set Cutoff Dir", display->line2);
    EXPECT_EQ(true, display->cursorOn);
    EXPECT_EQ(0, display->selectedLine);
}

TEST_F(ControllerTest, MainMenuScrolling) {
    controller->setScreen(controller->getMainMenu());

    rotary->setPosition(1);
    controller->tick(1234);
    EXPECT_STREQ("1 Set Cutoff V  ", display->line1);
    EXPECT_STREQ("2 Set Cutoff Dir", display->line2);
    EXPECT_EQ(1, display->selectedLine);

    rotary->setPosition(2);
    controller->tick(2222);
    EXPECT_STREQ("2 Set Cutoff Dir", display->line1);
    EXPECT_STREQ("3 Adjust +V Intf", display->line2);
    EXPECT_EQ(1, display->selectedLine);

    rotary->setPosition(3);
    controller->tick(3333);
    EXPECT_STREQ("3 Adjust +V Intf", display->line1);
    EXPECT_STREQ("4 Adjust -V Intf", display->line2);
    EXPECT_EQ(1, display->selectedLine);

    rotary->setPosition(4);
    controller->tick(4444);
    EXPECT_STREQ("4 Adjust -V Intf", display->line1);
    EXPECT_STREQ("5 Set Warn Buff ", display->line2);
    EXPECT_EQ(1, display->selectedLine);

    rotary->setPosition(5);
    controller->tick(5555);
    EXPECT_STREQ("4 Adjust -V Intf", display->line1);
    EXPECT_STREQ("5 Set Warn Buff ", display->line2);
    EXPECT_EQ(1, display->selectedLine);

    rotary->setPosition(4);
    controller->tick(6666);
    EXPECT_STREQ("4 Adjust -V Intf", display->line1);
    EXPECT_STREQ("5 Set Warn Buff ", display->line2);
    EXPECT_EQ(0, display->selectedLine);

    rotary->setPosition(2);
    controller->tick(7777);
    EXPECT_STREQ("3 Adjust +V Intf", display->line1);
    EXPECT_STREQ("4 Adjust -V Intf", display->line2);
    EXPECT_EQ(0, display->selectedLine);

    rotary->setPosition(-1);
    controller->tick(8888);
    EXPECT_STREQ("2 Set Cutoff Dir", display->line1);
    EXPECT_STREQ("3 Adjust +V Intf", display->line2);
    EXPECT_EQ(0, display->selectedLine);
}

TEST_F(ControllerTest, SelectingCutoffVItem) {
    controller->setScreen(controller->getMainMenu());
    rotary->setClicked(true);
    controller->tick(1234);

    EXPECT_STREQ("Cutoff Voltage", controller->getScreen()->getName());
    EXPECT_STREQ("Cutoff Voltage  ", display->line1);
    EXPECT_STREQ("-> 2.5 (was 2.5)", display->line2);
    EXPECT_EQ(1, display->cursorRow);
    EXPECT_EQ(5, display->cursorCol);
}

TEST_F(ControllerTest, ChangingCutoffVoltageValue) {
    config->cutoffVoltage = 3.1;
    controller->setScreen(controller->getCutoffVoltageScreen());
    EXPECT_STREQ("-> 3.1 (was 3.1)", display->line2);

    rotary->setPosition(3);
    controller->tick(1000);
    EXPECT_STREQ("-> 3.4 (was 3.1)", display->line2);

    rotary->setPosition(-3);
    controller->tick(2000);
    EXPECT_STREQ("-> 2.8 (was 3.1)", display->line2);

    rotary->setPosition(100);
    controller->tick(3000);
    EXPECT_STREQ("-> 5.0 (was 3.1)", display->line2);

    rotary->setPosition(99);
    controller->tick(4000);
    EXPECT_STREQ("-> 4.9 (was 3.1)", display->line2);

    rotary->setPosition(-100);
    controller->tick(5000);
    EXPECT_STREQ("-> 0.0 (was 3.1)", display->line2);

    rotary->setPosition(-99);
    controller->tick(6000);
    EXPECT_STREQ("-> 0.1 (was 3.1)", display->line2);
}

TEST_F(ControllerTest, SavingCutoffVoltage) {
    controller->setScreen(controller->getCutoffVoltageScreen());
    rotary->setPosition(3);
    controller->tick(1000);

    EXPECT_STREQ("-> 2.8 (was 2.5)", display->line2);

    rotary->setClicked(true);
    controller->tick(2000);

    EXPECT_STREQ("Home", controller->getScreen()->getName());
    EXPECT_NEAR(2.8, config->cutoffVoltage, 0.01);
    EXPECT_EQ(true, config->saved);
}

TEST_F(ControllerTest, SelectingCuttoffDirection) {
    controller->setScreen(controller->getMainMenu());
    rotary->setPosition(1);
    controller->tick(1111);
    rotary->setClicked(true);
    controller->tick(2222);

    EXPECT_STREQ("Cutoff Direction", controller->getScreen()->getName());
    EXPECT_STREQ("Cutoff Direction", display->line1);
    EXPECT_STREQ("< 2.5V or > 2.5V", display->line2);
    EXPECT_EQ(1, display->cursorRow);
    EXPECT_EQ(0, display->cursorCol);
}

TEST_F(ControllerTest, SavingCutoffDirection) {
    controller->setScreen(controller->getCutoffDirectionScreen());
    rotary->setPosition(1);
    controller->tick(1111);
    EXPECT_EQ(10, display->cursorCol);

    rotary->setClicked(true);
    controller->tick(2222);

    EXPECT_STREQ("Home", controller->getScreen()->getName());
    EXPECT_EQ('>', config->cutoffDirection);
    EXPECT_EQ(true, config->saved);
}

TEST_F(ControllerTest, SelectingLoadPosVoltageInterference) {
    controller->setScreen(controller->getMainMenu());
    rotary->setPosition(1);
    controller->tick(1111);
    rotary->setPosition(2);
    controller->tick(2222);
    rotary->setClicked(true);
    controller->tick(3333);

    EXPECT_STREQ("Adjust +V Intrf", controller->getScreen()->getName());
    EXPECT_STREQ("Adjust +V Intrf ", display->line1);
    EXPECT_STREQ("-> 0.0 (was 0.0)", display->line2);
    EXPECT_EQ(1, display->cursorRow);
    EXPECT_EQ(5, display->cursorCol);
}

TEST_F(ControllerTest, SavingLoadPosVoltageInterference) {
    controller->setScreen(controller->getAdjustPInterferenceScreen());
    rotary->setPosition(-12);
    controller->tick(1111);
    EXPECT_STREQ("->-1.2 (was 0.0)", display->line2);

    rotary->setClicked(true);
    controller->tick(2222);

    EXPECT_STREQ("Home", controller->getScreen()->getName());
    EXPECT_NEAR(-1.2, config->pVoltageInterference, 0.01);
    EXPECT_NEAR(-1.2, loadPositive->getInterferenceAdjustment(), 0.01);
    EXPECT_EQ(true, config->saved);
}

TEST_F(ControllerTest, SelectingLoadNegVoltageInterference) {
    controller->setScreen(controller->getMainMenu());
    rotary->setPosition(1);
    controller->tick(1111);
    rotary->setPosition(2);
    controller->tick(2222);
    rotary->setPosition(3);
    controller->tick(3333);
    rotary->setClicked(true);
    controller->tick(4444);

    EXPECT_STREQ("Adjust -V Intrf", controller->getScreen()->getName());
    EXPECT_STREQ("Adjust -V Intrf ", display->line1);
    EXPECT_STREQ("-> 0.0 (was 0.0)", display->line2);
    EXPECT_EQ(1, display->cursorRow);
    EXPECT_EQ(5, display->cursorCol);
}

TEST_F(ControllerTest, SavingLoadNegVoltageInterference) {
    controller->setScreen(controller->getAdjustNInterferenceScreen());
    rotary->setPosition(-6);
    controller->tick(1111);
    EXPECT_STREQ("->-0.6 (was 0.0)", display->line2);

    rotary->setClicked(true);
    controller->tick(2222);

    EXPECT_STREQ("Home", controller->getScreen()->getName());
    EXPECT_NEAR(-0.6, config->nVoltageInterference, 0.01);
    EXPECT_NEAR(-0.6, loadNegative->getInterferenceAdjustment(), 0.01);
    EXPECT_EQ(true, config->saved);
}

TEST_F(ControllerTest, WarningBufferScreen) {
    controller->setScreen(controller->getMainMenu());
    rotary->setPosition(1);
    controller->tick(1111);
    rotary->setPosition(2);
    controller->tick(2222);
    rotary->setPosition(3);
    controller->tick(3333);
    rotary->setPosition(4);
    controller->tick(4444);
    rotary->setClicked(true);
    controller->tick(5555);

    EXPECT_STREQ("Warning Buffer", controller->getScreen()->getName());
    EXPECT_STREQ("Warning Buffer  ", display->line1);
    EXPECT_STREQ("-> 0.0 (was 0.0)", display->line2);
    EXPECT_EQ(1, display->cursorRow);
    EXPECT_EQ(5, display->cursorCol);
}

TEST_F(ControllerTest, ChangingWarningBuffer) {
    controller->setScreen(controller->getWarningBufferScreen());
    rotary->setPosition(3);
    controller->tick(1111);
    EXPECT_STREQ("-> 0.3 (was 0.0)", display->line2);

    rotary->setClicked(true);
    controller->tick(2222);

    EXPECT_STREQ("Home", controller->getScreen()->getName());
    EXPECT_NEAR(0.3, config->warningBuffer, 0.01);
    EXPECT_EQ(true, config->saved);
}

TEST_F(ControllerTest, StateIdleToMonitoring) {
    loadPositive->volts = 0.0;
    EXPECT_STREQ("IDL", controller->getState()->abrv());
    controller->tick(1000);
    EXPECT_STREQ("IDL", controller->getState()->abrv());

    loadPositive->volts = 4.2;
    controller->tick(2000);
    EXPECT_STREQ("MON", controller->getState()->abrv());
}

TEST_F(ControllerTest, MonitorToWarn) {
    config->warningBuffer = 0.2;
    loadPositive->volts = 4.2;
    controller->setState(controller->getMonitorState());
    controller->tick(1000);
    EXPECT_STREQ("MON", controller->getState()->abrv());
    EXPECT_EQ(true, load->isOn());

    loadPositive->volts = 2.7;
    controller->tick(2000);
    EXPECT_STREQ("WRN", controller->getState()->abrv());
}

TEST_F(ControllerTest, WarnToAlarm) {
    config->warningBuffer = 0.2;
    loadPositive->volts = 2.7;
    controller->setState(controller->getWarnState());
    controller->tick(1000);
    EXPECT_STREQ("WRN", controller->getState()->abrv());
    EXPECT_EQ(1, warning->timesPlayed);

    loadPositive->volts = 2.5;
    controller->tick(2000);
    EXPECT_STREQ("ALM", controller->getState()->abrv());
}

TEST_F(ControllerTest, WarnBackToMon) {
    config->warningBuffer = 0.2;
    loadPositive->volts = 2.7;
    controller->setState(controller->getWarnState());
    controller->tick(1000);

    loadPositive->volts = 2.8;
    controller->tick(2000);
    EXPECT_STREQ("WRN", controller->getState()->abrv());
    EXPECT_EQ(2, warning->timesPlayed);

    loadPositive->volts = 2.9;
    controller->tick(3000);
    EXPECT_STREQ("WRN", controller->getState()->abrv());
    EXPECT_EQ(3, warning->timesPlayed);

    loadPositive->volts = 3.0;
    controller->tick(4000);
    EXPECT_STREQ("MON", controller->getState()->abrv());
}

TEST_F(ControllerTest, AlarmBackToWarn) {
    config->warningBuffer = 0.2;
    loadPositive->volts = 2.5;
    load->on();
    controller->setState(controller->getAlarmState());
    controller->tick(1000);
    EXPECT_EQ(false, load->isOn());

    loadPositive->volts = 2.6;
    controller->tick(2000);
    EXPECT_STREQ("ALM", controller->getState()->abrv());
    EXPECT_EQ(2, alarm->timesPlayed);

    loadPositive->volts = 2.7;
    controller->tick(3000);
    EXPECT_STREQ("ALM", controller->getState()->abrv());
    EXPECT_EQ(3, alarm->timesPlayed);

    loadPositive->volts = 3.0;
    controller->tick(4000);
    EXPECT_STREQ("WRN", controller->getState()->abrv());

    controller->tick(5000);
    EXPECT_EQ(true, load->isOn());
}

TEST_F(ControllerTest, AlarmToIdleByPress) {
    config->warningBuffer = 0.2;
    loadPositive->volts = 2.5;
    load->on();
    controller->setState(controller->getAlarmState());
    controller->tick(1000);

    rotary->setClicked(true);
    controller->tick(2000);
    EXPECT_STREQ("IDL", controller->getState()->abrv());

    controller->tick(3000);
    EXPECT_EQ(false, load->isOn());
}
