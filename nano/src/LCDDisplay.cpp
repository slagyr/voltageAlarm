#include "Arduino.h"
#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(LiquidCrystal *lcd) {
    this->lcd = lcd;
}

void LCDDisplay::setLine1(const char *line) {
    Serial.print("Line1: ");
    Serial.print("line: ");
    Serial.println(line);
    lcd->setCursor(0, 0);
    lcd->print(line);
}

void LCDDisplay::setLine2(const char *line) {
    Serial.print("line2: ");
    Serial.println(line);
    lcd->setCursor(0, 1);
    lcd->print(line);
}
