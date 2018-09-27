#include "Arduino.h"
#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(LiquidCrystal *lcd) {
    this->lcd = lcd;
    lcd->begin(16, 2);
    lcd->noCursor();
    lcd->noBlink();
    lcd->clear();
}

void LCDDisplay::showLines(const char *line1, const char *line2) {
    showLine1(line1);
    showLine2(line2);
}

void LCDDisplay::showLine1(const char *line) {
    lcd->setCursor(0, 0);
    lcd->print(line);
    if(cursorOn && cursorRow == 0)
        updateCursor();
}

void LCDDisplay::showLine2(const char *line) {
    lcd->setCursor(0, 1);
    lcd->print(line);
    if(cursorOn && cursorRow == 1)
        updateCursor();
}

void LCDDisplay::selectLine(uint8_t line) {
    showCursorAt(line, 0);
}

void LCDDisplay::showCursorAt(uint8_t row, uint8_t col) {
    cursorOn = true;
    cursorRow = row;
    cursorCol = col;
    updateCursor();
}

void LCDDisplay::updateCursor() const {
    lcd->setCursor(cursorCol, cursorRow);
    lcd->cursor();
    lcd->blink();
}

void LCDDisplay::hideCursor() {
    cursorOn = false;
    lcd->noCursor();
    lcd->noBlink();
}
