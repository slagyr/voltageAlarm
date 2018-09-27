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
}

void Controller::setup() {
    rotary->setup();
    setScreen(splash);
}

Screen *Controller::getScreen() {
    return screen;
}

void Controller::setScreen(Screen *screen) {
    hardware->println(screen->getName());
    this->screen = screen;
    hardware->println("calling screen->enter()");
    screen->enter();
}

Display *Controller::getDisplay() {
    return display;
}

void Controller::tick(unsigned long millis) {
//    hardware->println("Controller::tick");
    if (millis > lastUserEventTime + screen->getIdleTimeout()) {
        hardware->println("screen timeout");
        setScreen(getHomeScreen());
        lastUserEventTime = millis;
        lastUpdate = millis;
    } else if (rotary->hasUpdate()) {
        hardware->println("rotary hasUpdate");
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

Screen::Screen(Controller *controller, const char *name) {
    this->controller = controller;
    this->name = name;
}

Splash::Splash(Controller *controller) : Screen(controller, "Splash") {
    timeout = 1000;
}

void Splash::enter() {
    controller->getDisplay()->hideCursor();
    controller->getHardware()->println("Splash::enter");
    controller->getDisplay()->showLines("Volt Alarm v1.0", "Micah Martin");
}

void Splash::update() {
    // do nothing
}

int ones(double d) {
    return (int) (d + 0.05) % 10;
}

int tenths(double d) {
    return (int) (d * 10 + 0.5) % 10;
}

bool dEq(double d1, double d2) {
    double diff = d1 - d2;
    return -0.05 < diff && diff < 0.5;
}

HomeScreen::HomeScreen(Controller *controller) : Screen(controller, "Home") {
    timeout = 60000;
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
    bool pVoltChanged = !dEq(lastPVolts, pVolts);
    bool nVoltChanged = !dEq(lastNVolts, nVolts);

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

MainMenu::MainMenu(Controller *controller) : Screen(controller, "Main Menu") {
}


void MainMenu::enter() {
    selectedIndex = 0;
    scrollingDown = false;
    lastRotaryPosition = 0;
    screens[0] = controller->getCutoffVoltageScreen();
    screens[1] = controller->getHomeScreen();
    screens[2] = controller->getHomeScreen();
    screens[3] = controller->getHomeScreen();
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

CutoffVoltageScreen::CutoffVoltageScreen(Controller *controller) : Screen(controller, "Cutoff Voltage") {}

void CutoffVoltageScreen::enter() {
    oldValue = controller->getConfig()->cutoffVoltage;
    newValue = oldValue;
    controller->getDisplay()->showLine1("Cutoff Voltage  ");
    updateValue();
    controller->getDisplay()->showCursorAt(1, 5);
    lastRotaryPosition = controller->getRotary()->getPosition();
}

void CutoffVoltageScreen::updateValue() const {
    char line[17];
    sprintf(line, "-> %i.%i (was %i.%i)",
            ones(newValue), tenths(newValue), ones(oldValue), tenths(oldValue));
    controller->getDisplay()->showLine2(line);
}

void CutoffVoltageScreen::update() {
    Rotary *rotary = controller->getRotary();
    if (rotary->hasUpdate()) {
        if (rotary->wasClicked()) {
            controller->getConfig()->cutoffVoltage = newValue;
            controller->getConfig()->save();
            controller->setScreen(controller->getHomeScreen());
        } else {
            int position = rotary->getPosition();
            int diff = position - lastRotaryPosition;
            newValue += 0.1 * diff;
            if (newValue > 5.0)
                newValue = 5.0;
            else if (newValue < 0)
                newValue = 0;
            updateValue();
            lastRotaryPosition = position;
        }
    }
}

