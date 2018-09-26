#ifndef DISPLAY_H
#define DISPLAY_H


class Display {

public:
    virtual void showLines(const char *line1, const char *line2) = 0;
    virtual void showLine1(const char *line) = 0;
    virtual void showLine2(const char *line) = 0;

    virtual void selectLine(int line) = 0;

    virtual void showCursorAt(int row, int col) = 0;

    virtual void hideCursor() = 0;
};


#endif
