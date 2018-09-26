
#include "Hardware.h"
#include "VoltageSensor.h"

#define AnalogToVoltMultiplier 0.004887585532747;

VoltageSensor::VoltageSensor(Hardware *hardware, uint8_t pin, double inteferenceAdjustment) {
    this->hardware = hardware;
    this->pin = pin;
    this->interferenceAdjustment = inteferenceAdjustment;
}

Hardware *VoltageSensor::getHardware() {
    return hardware;
}

uint8_t VoltageSensor::getPin() {
    return pin;
}

double VoltageSensor::readVoltage() {
    int analogValue = hardware->readAnalogPin(pin);
    double voltage = analogValue * AnalogToVoltMultiplier;
    return voltage + interferenceAdjustment;
}

void VoltageSensor::setInterferenceAdjustment(double error) {
    interferenceAdjustment = error;
}

double VoltageSensor::getInterferenceAdjustment() {
    return interferenceAdjustment;
}
