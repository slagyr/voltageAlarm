#include "Controller.h"

#ifndef ARDUINO_H
    #include "stdio.h"
#endif

Controller::Controller(Hardware *hardware, VoltageSensor *loadPositive, VoltageSensor *loadNegative, Display *display) {
    this->hardware = hardware;
    this->loadPositive = loadPositive;
    this->loadNegative = loadNegative;
    this->display = display;
    lastUserEventTime = 0;
    cutoffVoltage = 5.0;
    cutoffAbove = false;

    splash = new Splash(this);
    homeScreen = new HomeScreen(this);

    screen = splash;
}

Screen *Controller::getScreen() {
    return screen;
}

void Controller::setScreen(Screen *screen) {
    this->screen = screen;
}

Display *Controller::getDisplay() {
    return display;
}

void Controller::tick(unsigned long millis) {
    if (millis > lastUserEventTime + screen->getIdleTimeout())
        screen->timeout();
    screen->update();
}

Screen *Controller::getHomeScreen() {
    return homeScreen;
}

VoltageSensor* Controller::getLoadPositiveSensor() {
    return loadPositive;
}

VoltageSensor* Controller::getLoadNegativeSensor() {
    return loadNegative;
}

bool Controller::isCutoffAbove() {
    return cutoffAbove;
}

double Controller::getCutoffVoltage() {
    return cutoffVoltage;
}

void Controller::setCutoffVoltage(double voltage) {
    cutoffVoltage = voltage;
}

void Controller::setCutoffAbove(bool b) {
    cutoffAbove = b;
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

void Splash::update() {
    if(!loaded) {
        controller->getDisplay()->show("Volt Alarm v1.0", "Micah Martin");
        loaded = true;
    }
}

void Splash::timeout() {
    controller->setScreen(controller->getHomeScreen());
}

void HomeScreen::timeout() {
    // doesn't timeout
}

int ones(double d) {
    return (int)(d + 0.05) % 10;
}

int tenths(double d) {
    return (int)(d * 10 + 0.5) % 10;
}

bool dEq(double d1, double d2) {
    double diff = d1 - d2;
    return -0.05 < diff && diff < 0.5;
}

void HomeScreen::update() {
    double pVolts = controller->getLoadPositiveSensor()->readVoltage();
    double nVolts = controller->getLoadNegativeSensor()->readVoltage();
    bool pVoltChanged = !dEq(lastPVolts, pVolts);
    bool nVoltChanged = !dEq(lastNVolts, nVolts);

    if(pVoltChanged || nVoltChanged) {
        lastPVolts = pVolts;
        lastNVolts = nVolts;

        char line1[17];
        char line2[17];

        const char *direction = controller->isCutoffAbove() ? ">" : "<";
        double cVolts = controller->getCutoffVoltage();

        sprintf(line1, "Voltage: %i.%i %i.%i",
                ones(pVolts), tenths(pVolts), ones(nVolts), tenths(nVolts));
        sprintf(line2, "Cutoff: %s %i.%i   ", direction, ones(cVolts), tenths(cVolts));

        controller->getDisplay()->show(line1, line2);
    }
}
