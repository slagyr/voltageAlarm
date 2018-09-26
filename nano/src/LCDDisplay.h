#ifndef NANO_LCDDISPLAY_H
#define NANO_LCDDISPLAY_H

#include <LiquidCrystal.h>
#include "Display.h"

class LCDDisplay : public Display {
public:
    LCDDisplay(LiquidCrystal *lcd);
    void show(const char *line1, const char *line2) override;

    LiquidCrystal *lcd;
};


#endif //NANO_LCDDISPLAY_H
