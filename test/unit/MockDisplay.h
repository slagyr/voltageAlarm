#ifndef MOCKDISPLAY_H
#define MOCKDISPLAY_H

#include "Display.h"

#include <cstring>

class MockDisplay : public Display {

public:

    void setLine1(const char *line) override { strcpy(line1, line); }
    void setLine2(const char *line) override { strcpy(line2, line); }

    char line1[17];
    char line2[17];
};

#endif
