#ifndef MOCKDISPLAY_H
#define MOCKDISPLAY_H

#include "Display.h"

#include <cstring>

class MockDisplay : public Display {

public:

    void showLines(const char *l1, const char *l2) override {
        showLine1(l1);
        showLine2(l2);
    }

    void showLine1(const char *line) override {
        strcpy(line1, line);
    }

    void showLine2(const char *line) override {
        strcpy(line2, line);
    }

    void selectLine(int line) override {
        selectedLine = line;
        showCursorAt(line, 0);
    }

    void showCursorAt(int row, int col) override {
        cursorOn = true;
        cursorRow = row;
        cursorCol = col;
    }

    void hideCursor() override {
        cursorOn = false;
    }

    char line1[17];
    char line2[17];
    bool cursorOn = false;
    int selectedLine = -1;
    int cursorRow;
    int cursorCol;
};

#endif
