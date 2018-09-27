#ifndef DISPLAY_H
#define DISPLAY_H

typedef unsigned char uint8_t;

class Display {

public:
    virtual void showLines(const char *line1, const char *line2) = 0;
    virtual void showLine1(const char *line) = 0;
    virtual void showLine2(const char *line) = 0;

    virtual void selectLine(uint8_t line) = 0;

    virtual void showCursorAt(uint8_t row, uint8_t col) = 0;

    virtual void hideCursor() = 0;
};


#endif
