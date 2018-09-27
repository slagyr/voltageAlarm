#include "Controller.h"

#ifndef ARDUINO_H

#include "stdio.h"

#endif

Controller::Controller(Hardware *hardware,
                       VoltageSensor *loadPositive,
                       VoltageSensor *loadNegative,
                       Display *display,
                       Rotary *rotary,
                       Config *config) {
    this->hardware = hardware;
    this->loadPositive = loadPositive;
    this->loadNegative = loadNegative;
    this->display = display;
    this->rotary = rotary;
    this->config = config;
    lastUserEventTime = 0;

    splash = new Splash(this);
    homeScreen = new HomeScreen(this);
    mainMenu = new MainMenu(this);
    cutoffVoltageScreen = new CutoffVoltageScreen(this);
    cutoffDirectionScreen = new CutoffDirectionScreen(this);
    adjustPInterferenceScreen = new AdjustPInterefenceScreen(this);
    adjustNInterferenceScreen = new AdjustNInterefenceScreen(this);
}

void Controller::setup() {
    rotary->setup();

    loadPositive->setInterferenceAdjustment(config->pVoltageInterference);
    loadNegative->setInterferenceAdjustment(config->nVoltageInterference);

    setScreen(splash);
}

Screen *Controller::getScreen() {
    return screen;
}

void Controller::setScreen(Screen *screen) {
    this->screen = screen;
    screen->enter();
}

Display *Controller::getDisplay() {
    return display;
}

void Controller::tick(unsigned long millis) {
//    hardware->println("Controller::tick");
    if (millis > lastUserEventTime + screen->getIdleTimeout()) {
        setScreen(getHomeScreen());
        lastUserEventTime = millis;
        lastUpdate = millis;
    } else if (rotary->hasUpdate()) {
        lastUserEventTime = millis;
        lastUpdate = millis;
        screen->update();
        rotary->rest();
    } else if (millis - lastUpdate > IdleUpdateInterval) {
        lastUpdate = millis;
        screen->update();
    }
}

Screen *Controller::getHomeScreen() {
    return homeScreen;
}

VoltageSensor *Controller::getLoadPositiveSensor() {
    return loadPositive;
}

VoltageSensor *Controller::getLoadNegativeSensor() {
    return loadNegative;
}

Hardware *Controller::getHardware() const {
    return hardware;
}

VoltageSensor *Controller::getLoadPositive() const {
    return loadPositive;
}

VoltageSensor *Controller::getLoadNegative() const {
    return loadNegative;
}

Rotary *Controller::getRotary() const {
    return rotary;
}

Config *Controller::getConfig() const {
    return config;
}

Screen *Controller::getMainMenu() {
    return mainMenu;
}

Screen *Controller::getCutoffVoltageScreen() const {
    return cutoffVoltageScreen;
}

Screen *Controller::getCutoffDirectionScreen() const {
    return cutoffDirectionScreen;
}

Screen *Controller::getAdjustPInterferenceScreen() const {
    return adjustPInterferenceScreen;
}

Screen *Controller::getAdjustNInterferenceScreen() const {
    return adjustNInterferenceScreen;
}

Screen::Screen(Controller *controller) {
    this->controller = controller;
}

Splash::Splash(Controller *controller) : Screen(controller) {}

void Splash::enter() {
    controller->getDisplay()->hideCursor();
    controller->getDisplay()->showLines("Volt Alarm v1.0", "Micah Martin");
}

void Splash::update() {
    // do nothing
}

unsigned long Splash::getIdleTimeout() {
    return 1000;
}

const char *Splash::getName() {
    return "Splash";
}

char sign(float d) {
    return d < 0 ? '-' : ' ';
}

int ones(float d) {
    d = d < 0 ? d * -1 : d;
    return (int) (d + 0.05) % 10;
}

int tenths(float d) {
    d = d < 0 ? d * -1 : d;
    return (int) (d * 10 + 0.5) % 10;
}

bool fEq(float d1, float d2) {
    float diff = d1 - d2;
    return -0.05 < diff && diff < 0.5;
}

HomeScreen::HomeScreen(Controller *controller) : Screen(controller) {}

unsigned long HomeScreen::getIdleTimeout() {
    return 60000;
}

const char *HomeScreen::getName() {
    return "Home";
}

void HomeScreen::enter() {
    controller->getDisplay()->hideCursor();
    updateInfo(true);
}

void HomeScreen::update() {
    if (controller->getRotary()->wasClicked())
        controller->setScreen(controller->getMainMenu());
    else
        updateInfo(false);
}

void HomeScreen::updateInfo(bool force) {
    double pVolts = controller->getLoadPositiveSensor()->readVoltage();
    double nVolts = controller->getLoadNegativeSensor()->readVoltage();
    bool pVoltChanged = !fEq(lastPVolts, pVolts);
    bool nVoltChanged = !fEq(lastNVolts, nVolts);

    if (force || pVoltChanged || nVoltChanged) {
        lastPVolts = pVolts;
        lastNVolts = nVolts;

        char line1[17];
        char line2[17];

        const char direction = controller->getConfig()->cutoffDirection;
        double cVolts = controller->getConfig()->cutoffVoltage;

        sprintf(line1, "Voltage: %i.%i %i.%i",
                ones(pVolts), tenths(pVolts), ones(nVolts), tenths(nVolts));
        sprintf(line2, "Cutoff: %c %i.%i   ", direction, ones(cVolts), tenths(cVolts));

        controller->getDisplay()->showLines(line1, line2);
    }
}

MainMenu::MainMenu(Controller *controller) : Screen(controller) {
}

const char *MainMenu::getName() {
    return "Main Menu";
}

void MainMenu::enter() {
    selectedIndex = 0;
    scrollingDown = false;
    lastRotaryPosition = 0;
    screens[0] = controller->getCutoffVoltageScreen();
    screens[1] = controller->getCutoffDirectionScreen();
    screens[2] = controller->getAdjustPInterferenceScreen();
    screens[3] = controller->getAdjustNInterferenceScreen();
    updateDisplay(0);
}

void MainMenu::update() {
    Rotary *rotary = controller->getRotary();
    if (rotary->hasUpdate()) {
        if (rotary->wasClicked()) {
            controller->setScreen(screens[selectedIndex]);
        } else {
            int position = rotary->getPosition();
            int top;
            if (position > lastRotaryPosition) {
                scrollingDown = true;
                selectedIndex += selectedIndex == 3 ? 0 : 1;
                top = selectedIndex - 1;
                updateDisplay(top);
            } else if (position < lastRotaryPosition) {
                scrollingDown = false;
                selectedIndex += selectedIndex == 0 ? 0 : -1;
                top = selectedIndex;
                updateDisplay(top);
            }
            lastRotaryPosition = position;
        }
    }
}

void MainMenu::updateDisplay(int top) const {
    Display *display = controller->getDisplay();
    display->showLines(items[top], items[top + 1]);
    display->selectLine(scrollingDown ? 1 : 0);
}

VotageUpdateScreen::VotageUpdateScreen(Controller *controller) : Screen(controller) {}

void VotageUpdateScreen::enter() {
    oldValue = storedValue();
    newValue = oldValue;
    controller->getDisplay()->showLine1(title());
    updateValue();
    controller->getDisplay()->showCursorAt(1, 5);
    lastRotaryPosition = controller->getRotary()->getPosition();
}

void VotageUpdateScreen::updateValue() const {
    char line[17];
    sprintf(line, "->%c%i.%i (was%c%i.%i)",
            sign(newValue), ones(newValue), tenths(newValue),
            sign(oldValue), ones(oldValue), tenths(oldValue));
    controller->getDisplay()->showLine2(line);
}

void VotageUpdateScreen::update() {
    Rotary *rotary = controller->getRotary();
    if (rotary->hasUpdate()) {
        if (rotary->wasClicked()) {
            updateStoredValue(newValue);
            controller->getConfig()->save();
            controller->setScreen(controller->getHomeScreen());
        } else {
            int position = rotary->getPosition();
            int diff = position - lastRotaryPosition;
            newValue += 0.1 * diff;
            if (newValue > maxVoltage())
                newValue = maxVoltage();
            else if (newValue < minVoltage())
                newValue = minVoltage();
            updateValue();
            lastRotaryPosition = position;
        }
    }
}

CutoffVoltageScreen::CutoffVoltageScreen(Controller *controller) : VotageUpdateScreen(controller) {}

const char *CutoffVoltageScreen::getName() { return "Cutoff Voltage";}

float CutoffVoltageScreen::storedValue() const {
    return Screen::controller->getConfig()->cutoffVoltage;
}

const char *CutoffVoltageScreen::title() { return "Cutoff Voltage  ";}

float CutoffVoltageScreen::minVoltage() const { return 0; }

float CutoffVoltageScreen::maxVoltage() const { return 5.0; }

void CutoffVoltageScreen::updateStoredValue(float value) const {
    Screen::controller->getConfig()->cutoffVoltage = value;
}

CutoffDirectionScreen::CutoffDirectionScreen(Controller *controller) : Screen(controller) {}

const char *CutoffDirectionScreen::getName() {
    return "Cutoff Direction";
}

void CutoffDirectionScreen::enter() {
    oldValue = controller->getConfig()->cutoffDirection;
    newValue = oldValue;

    float volts = controller->getConfig()->cutoffVoltage;
    int d1 = ones(volts);
    int d2 = tenths(volts);
    char line[17];
    sprintf(line, "< %i.%iV or > %i.%iV", d1, d2, d1, d2);

    controller->getDisplay()->showLine1("Cutoff Direction");
    controller->getDisplay()->showLine2(line);
    updateValue();
    lastRotaryPosition = controller->getRotary()->getPosition();
}

void CutoffDirectionScreen::update() {
    Rotary *rotary = controller->getRotary();
    if (rotary->hasUpdate()) {
        if (rotary->wasClicked()) {
            controller->getConfig()->cutoffDirection = newValue;
            controller->getConfig()->save();
            controller->setScreen(controller->getHomeScreen());
        } else {
            int position = rotary->getPosition();
            if (position > lastRotaryPosition)
                newValue = '>';
            else if (position < lastRotaryPosition)
                newValue = '<';
            updateValue();
            lastRotaryPosition = position;
        }
    }
}

void CutoffDirectionScreen::updateValue() const {
    if (newValue == '<')
        controller->getDisplay()->showCursorAt(1, 0);
    else
        controller->getDisplay()->showCursorAt(1, 10);
}

AdjustPInterefenceScreen::AdjustPInterefenceScreen(Controller *controller) : VotageUpdateScreen(controller) {}

const char *AdjustPInterefenceScreen::getName() {return "Adjust +V Intrf";}

float AdjustPInterefenceScreen::storedValue() const {
    return controller->getConfig()->pVoltageInterference;
}

const char *AdjustPInterefenceScreen::title() {return "Adjust +V Intrf ";}

float AdjustPInterefenceScreen::minVoltage() const { return -5.0f; }

float AdjustPInterefenceScreen::maxVoltage() const { return 5.0; }

void AdjustPInterefenceScreen::updateStoredValue(float value) const {
    controller->getLoadPositiveSensor()->setInterferenceAdjustment(value);
    controller->getConfig()->pVoltageInterference = value;
}

AdjustNInterefenceScreen::AdjustNInterefenceScreen(Controller *controller) : VotageUpdateScreen(controller) {}

const char *AdjustNInterefenceScreen::getName() {return "Adjust -V Intrf";}

float AdjustNInterefenceScreen::storedValue() const {
    return controller->getConfig()->nVoltageInterference;
}

const char *AdjustNInterefenceScreen::title() {return "Adjust -V Intrf ";}

float AdjustNInterefenceScreen::minVoltage() const { return -5.0f; }

float AdjustNInterefenceScreen::maxVoltage() const { return 5.0; }

void AdjustNInterefenceScreen::updateStoredValue(float value) const {
    controller->getLoadNegativeSensor()->setInterferenceAdjustment(value);
    controller->getConfig()->nVoltageInterference = value;
}