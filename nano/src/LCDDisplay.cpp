#include "Arduino.h"
#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(LiquidCrystal *lcd) {
    this->lcd = lcd;
    lcd->begin(16, 2);
}

void LCDDisplay::show(const char *line1, const char *line2) {

    lcd->setCursor(0, 0);
    lcd->print(line1);

    lcd->setCursor(0, 1);
    lcd->print(line2);
}
