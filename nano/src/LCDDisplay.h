#ifndef NANO_LCDDISPLAY_H
#define NANO_LCDDISPLAY_H

#include <LiquidCrystal.h>
#include "Display.h"

class LCDDisplay : public Display {
public:
    LCDDisplay(LiquidCrystal *lcd);
    void setLine1(const char *line) override;

    void setLine2(const char *line) override;

    LiquidCrystal *lcd;
};


#endif //NANO_LCDDISPLAY_H
