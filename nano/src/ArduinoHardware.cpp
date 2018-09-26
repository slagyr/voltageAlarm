#include "ArduinoHardware.h"
#include "Arduino.h"

void ArduinoHardware::pinToInput(uint8_t pin) {
    pinMode(pin, INPUT);
}


void ArduinoHardware::pinToOutput(uint8_t pin) {
    pinMode(pin, OUTPUT);

}

int ArduinoHardware::readDigitalPin(uint8_t pin) {
    return digitalRead(pin);
}

int ArduinoHardware::readAnalogPin(uint8_t pin) {
    return analogRead(pin);
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

void ArduinoHardware::playNote(uint8_t pin, unsigned int frequency, unsigned long duration) {
    tone(pin, frequency, duration);
}

void ArduinoHardware::sleep(unsigned long duration) {
    delay(duration);
}

