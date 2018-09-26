#include "Controller.h"

#include "stdio.h"

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
    controller->getDisplay()->setLine1("Volt Alarm v1.0");
    controller->getDisplay()->setLine2("Micah Martin");
}

void Splash::timeout() {
    controller->setScreen(controller->getHomeScreen());
}

void HomeScreen::timeout() {
    // doesn't timeout
}

void HomeScreen::update() {
    char line1[17];
    char line2[17];

    double pVolts = controller->getLoadPositiveSensor()->readVoltage();
    double nVolts = controller->getLoadNegativeSensor()->readVoltage();
    const char *direction = controller->isCutoffAbove() ? ">" : "<";
    double cVolts = controller->getCutoffVoltage();

    sprintf(line1, "Voltage: %1.1f %1.1f", pVolts, nVolts);
    sprintf(line2, "Cutoff: %s %1.1f", direction, cVolts);

    controller->getDisplay()->setLine1(line1);
    controller->getDisplay()->setLine2(line2);
}
