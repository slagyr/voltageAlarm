#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Display.h"
#include "Hardware.h"
#include "VoltageSensor.h"
#include "Display.h"
#include "Rotary.h"
#include "Config.h"
#include "Music.h"
#include "Switch.h"

// Will prevent screen from updating more than 5 times per second
#define IDLE_UPDATE_INTERVAL 200
#define VOLT_READ_INTERVAL 200

class Controller;

class Screen {
public:
    virtual unsigned long getIdleTimeout() { return 5000; };

    virtual const char *getName() = 0;

    virtual void enter() = 0;

    virtual void update() = 0;

protected:
    explicit Screen(Controller *controller);

    Controller *controller;
};

class Splash : public Screen {
public:

    explicit Splash(Controller *controller);

    unsigned long getIdleTimeout() override;

    const char *getName() override;

    void enter() override;

    void update() override;
};

class HomeScreen : public Screen {
public:

    explicit HomeScreen(Controller *controller);

    unsigned long getIdleTimeout() override;

    const char *getName() override;

    void enter() override;

    void update() override;

    float lastPVolts = -99.9f;
    float lastNVolts = -99.9f;

    void updateInfo(bool force);
};

class MainMenu : public Screen {
public:
    explicit MainMenu(Controller *controller);

    const char *getName() override;

    void enter() override;

    void update() override;

    void updateDisplay(int top) const;

private:
    const char *item(int i) const;

    Screen *screen(int i) const;

    int selectedIndex;
    bool scrollingDown;
    int lastRotaryPosition;
};

class VotageUpdateScreen : public Screen {

public:
    VotageUpdateScreen(Controller *controller);

    virtual float storedValue() const = 0;

    virtual const char *title() = 0;

    virtual float minVoltage() const = 0;

    virtual float maxVoltage() const = 0;

    virtual void updateStoredValue(float value) const = 0;

    void enter() override;

    void update() override;

    void updateValue() const;

    float oldValue;
    float newValue;
    int lastRotaryPosition;
};

class CutoffVoltageScreen : public VotageUpdateScreen {
public:
    explicit CutoffVoltageScreen(Controller *controller);

    const char *getName() override;

    float storedValue() const override;

    const char *title() override;

    float minVoltage() const override;

    float maxVoltage() const override;

    void updateStoredValue(float value) const override;

};

class CutoffDirectionScreen : public Screen {
public:
    explicit CutoffDirectionScreen(Controller *controller);

    const char *getName() override;

    void enter() override;

    void update() override;

    void updateValue() const;

    char oldValue;
    char newValue;
    int lastRotaryPosition;
};

class AdjustPInterefenceScreen : public VotageUpdateScreen {
public:
    explicit AdjustPInterefenceScreen(Controller *controller);

    const char *getName() override;

    float storedValue() const override;

    const char *title() override;

    float minVoltage() const override;

    float maxVoltage() const override;

    void updateStoredValue(float value) const override;
};

class AdjustNInterefenceScreen : public VotageUpdateScreen {
public:
    explicit AdjustNInterefenceScreen(Controller *controller);

    const char *getName() override;

    float storedValue() const override;

    const char *title() override;

    float minVoltage() const override;

    float maxVoltage() const override;

    void updateStoredValue(float value) const override;
};

class WarningBufferScreen : public VotageUpdateScreen {
public:
    explicit WarningBufferScreen(Controller *controller);

    const char *getName() override;

    float storedValue() const override;

    const char *title() override;

    float minVoltage() const override;

    float maxVoltage() const override;

    void updateStoredValue(float value) const override;
};

class State {
public:
    State(Controller* controller);
    virtual const char *abrv() = 0;

    virtual void run(float v) = 0;

protected:
    Controller *controller;
};

class IdleState : public State {
public:
    explicit IdleState(Controller* controller);
    const char *abrv() override;

    void run(float v) override;
};

class MonitorState : public State {
public:
    explicit MonitorState(Controller* controller);
    const char *abrv() override;

    void run(float v) override;
};

class WarnState : public State {
public:
    explicit WarnState(Controller* controller);
    const char *abrv() override;

    void run(float v) override;
};

class AlarmState : public State {
public:
    explicit AlarmState(Controller* controller);
    const char *abrv() override;

    void run(float v) override;
};

class Controller {

public:
    Controller(Hardware *hardware,
               VoltageSensor *loadPositive,
               VoltageSensor *loadNegative,
               Display *display,
               Rotary *rotary,
               Config *config,
               Music *alarm,
               Music *warning,
               Switch *load);

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

    Music *getAlarm() const;

    Music *getWarning() const;

    Switch *getLoadSwitch() const;

    Screen *getHomeScreen();

    Screen *getMainMenu();

    Screen *getCutoffVoltageScreen() const;

    Screen *getCutoffDirectionScreen() const;

    Screen *getAdjustPInterferenceScreen() const;

    Screen *getAdjustNInterferenceScreen() const;

    Screen *getWarningBufferScreen() const;

    State *getState() const;

    void setState(State *state);

    State *getIdleState() const;

    State *getMonitorState() const;

    State *getWarnState() const;

    State *getAlarmState() const;

private:
    Hardware *hardware;
    VoltageSensor *loadPositive;
    VoltageSensor *loadNegative;
    Display *display;
    Rotary *rotary;
    Config *config;
    Music *alarm;
    Music *warning;
    Switch *loadSwitch;

    Screen *screen;
    Screen *splash;
    Screen *homeScreen;
    Screen *mainMenu;
    Screen *cutoffVoltageScreen;
    Screen *cutoffDirectionScreen;
    Screen *adjustPInterferenceScreen;
    Screen *adjustNInterferenceScreen;
    Screen *warningBufferScreen;

    State *state;
    State *idleState;
    State *monitorState;
    State *warnState;
    State *alarmState;

    unsigned long lastUserEventTime = 0;
    unsigned long lastUpdate = 0;
    unsigned long nextVoltReadTime = 0;
};


#endif
