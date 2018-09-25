
#ifndef ROTARY_H
#define ROTARY_H

#include "Hardware.h"

class Rotary {

public:

    static Rotary* init(Hardware *hardware, uint8_t sw, uint8_t dt, uint8_t clk);
    Hardware* getHardware();
    int getPosition();
    int getSW();
    int getDT();
    int getCLK();
    bool hasUpdate();
    void rest();
    void handleRotation();
    int getDebounceDelay();
    void setDebouceDelay(int delay);
    void handleClick();
    bool wasClicked();
    void setPosition(int position);

private:

    Hardware *hardware;
    uint8_t sw;
    uint8_t dt;
    uint8_t clk;
    int position;
    bool updated;
    int debounceDelay;
    unsigned long lastEventTime;
    bool clicked;

    Rotary(Hardware *hardware, uint8_t sw, uint8_t dt, uint8_t clk);
    void configurePins() const;
    bool notBounced();
};


#endif
