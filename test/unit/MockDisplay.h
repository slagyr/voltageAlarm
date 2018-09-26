#ifndef MOCKDISPLAY_H
#define MOCKDISPLAY_H

#include "Display.h"

#include <cstring>

class MockDisplay : public Display {

public:

    void show(const char *l1, const char *l2) override {
        strcpy(line1, l1);
        strcpy(line2, l2);
    }

    char line1[17];
    char line2[17];
};

#endif
