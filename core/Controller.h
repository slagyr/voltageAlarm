#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Display.h"
#include "Hardware.h"
#include "VoltageSensor.h"
#include "Display.h"

class Controller;

class Screen {
public:
    virtual const char *getName() = 0;

    virtual unsigned long getIdleTimeout() = 0;

    virtual void update() = 0;

    virtual void timeout() = 0;

protected:
    Screen(Controller *controller) { this->controller = controller; }

    Controller *controller;
};

class Splash : public Screen {
public:
    Splash(Controller *controller) : Screen(controller) {}

    const char *getName() override { return "Splash"; };

    unsigned long getIdleTimeout() override { return 5000; }

    void update() override;

    void timeout() override;

private:
    bool loaded = false;
};

class HomeScreen : public Screen {
public:
    HomeScreen(Controller *controller) : Screen(controller) {}

    const char *getName() override { return "Home"; };

    unsigned long getIdleTimeout() override { return 4294967295; }

    void update() override;

    void timeout() override;

    double lastPVolts = -99.9;
    double lastNVolts = -99.9;
};


class Controller {

public:
    Controller(Hardware *hardware,
               VoltageSensor *loadPositive,
               VoltageSensor *loadNegative,
               Display *display);

    Display *getDisplay();

    Screen *getScreen();

    void setScreen(Screen *screen);

    Screen *getHomeScreen();

    VoltageSensor *getLoadPositiveSensor();

    VoltageSensor *getLoadNegativeSensor();

    void tick(unsigned long millis);

    bool isCutoffAbove();

    void setCutoffAbove(bool b);

    double getCutoffVoltage();

    void setCutoffVoltage(double voltage);

    Hardware *getHardware() const;

    VoltageSensor *getLoadPositive() const;

    VoltageSensor *getLoadNegative() const;

private:

    Hardware *hardware;
    VoltageSensor *loadPositive;
    VoltageSensor *loadNegative;
    Display *display;
    Screen *screen;
    Screen *splash;
    Screen *homeScreen;
    unsigned long lastUserEventTime = 0;
    bool cutoffAbove = false;
    double cutoffVoltage = 5.0;
};


#endif
