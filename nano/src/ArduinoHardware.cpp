#include "ArduinoHardware.h"
#include "Arduino.h"

void ArduinoHardware::pinToInput(uint8_t pin) {
    pinMode(pin, INPUT);
}


int ArduinoHardware::readDigitalPin(uint8_t pin) {
    return digitalRead(pin);
}

unsigned long ArduinoHardware::getMillis() {
    return millis();
}

void ArduinoHardware::print(const char *value) {
    Serial.print(value);
}

void ArduinoHardware::print(int value) {
    Serial.print(value);
}

void ArduinoHardware::setPinHigh(uint8_t pin) {
    digitalWrite(pin, HIGH);
}

void ArduinoHardware::setPinLow(uint8_t pin) {
    digitalWrite(pin, LOW);
}
