#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Display.h"
#include "Hardware.h"
#include "VoltageSensor.h"
#include "Display.h"
#include "Rotary.h"
#include "Config.h"

// Will prevent screen from updating more than 5 times per second
#define IdleUpdateInterval 200

class Controller;

class Screen {
public:
    const char *getName() { return name; };

    unsigned long getIdleTimeout() { return timeout; };

    virtual void enter() = 0;

    virtual void update() = 0;

protected:
    Screen(Controller *controller, const char *name);

    Controller *controller;
    unsigned long timeout = 5000;
    const char *name;
};

class Splash : public Screen {
public:

    Splash(Controller *controller);

    void enter() override;

    void update() override;
};

class HomeScreen : public Screen {
public:

    HomeScreen(Controller *controller);

    void enter() override;

    void update() override;

    double lastPVolts = -99.9;
    double lastNVolts = -99.9;

    void updateInfo(bool force);
};

class MainMenu : public Screen {
public:
    MainMenu(Controller *controller);

    void enter() override;

    void update() override;

public:

    void updateDisplay(int top) const;

    const char *items[4] = {"1 Set Cutoff V  ",
                            "2 Set Cutoff Dir",
                            "3 Adjust +V Intf",
                            "4 Adjust -V Intf"};
    Screen *screens[4] = {nullptr, nullptr, nullptr, nullptr};
    int selectedIndex;
    bool scrollingDown;
    int lastRotaryPosition;
};

class CutoffVoltageScreen : public Screen {
public:
    CutoffVoltageScreen(Controller *controller);

    void enter() override;

    void update() override;

    void updateValue() const;

    float oldValue;
    float newValue;
    int lastRotaryPosition;
};


class Controller {

public:
    Controller(Hardware *hardware, VoltageSensor *loadPositive, VoltageSensor *loadNegative, Display *display,
                   Rotary *rotary, Config *config);

    void setup();

    Hardware *getHardware() const;

    VoltageSensor *getLoadPositiveSensor();

    VoltageSensor *getLoadNegativeSensor();

    Display *getDisplay();

    Rotary *getRotary() const;

    Config *getConfig() const;

    Screen *getScreen();

    void setScreen(Screen *screen);

    void tick(unsigned long millis);

    VoltageSensor *getLoadPositive() const;

    VoltageSensor *getLoadNegative() const;

    Screen *getHomeScreen();

    Screen *getMainMenu();

    Screen *getCutoffVoltageScreen() const;

private:
    Hardware *hardware;
    VoltageSensor *loadPositive;
    VoltageSensor *loadNegative;
    Display *display;
    Rotary *rotary;
    Config *config;

    Screen *screen;
    Screen *splash;
    Screen *homeScreen;
    Screen *mainMenu;
    Screen *cutoffVoltageScreen;

    unsigned long lastUserEventTime = 0;
    unsigned long lastUpdate = 0;

};


#endif
