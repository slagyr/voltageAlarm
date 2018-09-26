#ifndef DISPLAY_H
#define DISPLAY_H


class Display {

public:
    virtual void setLine1(const char *line) = 0;
    virtual void setLine2(const char *line) = 0;
};


#endif
