#ifndef HARDWARE_H
#define HARDWARE_H

typedef unsigned char uint8_t;

class Hardware {

public:
    virtual void pinToInput(uint8_t pin) = 0;
    virtual void pinToOutput(uint8_t pin) = 0;
    virtual int readDigitalPin(uint8_t pin) = 0;
    virtual int readAnalogPin(uint8_t pin) = 0;
    virtual unsigned long getMillis() = 0;
    virtual void setPinHigh(uint8_t pin) = 0;
    virtual void setPinLow(uint8_t pin) = 0;
    virtual void print(const char *value) = 0;
    virtual void print(int value) = 0;
    virtual void playNote(uint8_t pin, unsigned int frequency, unsigned long duration) = 0;

    virtual void sleep(unsigned long duration) = 0;

    void printValue(char* label, int value);
    void println(const char *value);
    void println(int value);
};


#endif
