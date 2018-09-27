#ifndef NANO_LCDDISPLAY_H
#define NANO_LCDDISPLAY_H

#include <LiquidCrystal.h>
#include "Display.h"

class LCDDisplay : public Display {
public:
    LCDDisplay(LiquidCrystal *lcd);
    void showLines(const char *line1, const char *line2) override;

    void showLine1(const char *line) override;

    void showLine2(const char *line) override;

    void selectLine(uint8_t line) override;

    void showCursorAt(uint8_t row, uint8_t col) override;

    void hideCursor() override;

    void updateCursor() const;

private:
    LiquidCrystal *lcd;
    bool cursorOn;
    uint8_t cursorRow;
    uint8_t cursorCol;

};


#endif //NANO_LCDDISPLAY_H
