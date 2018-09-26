#ifndef VOLTAGEALARM_CONFIG_H
#define VOLTAGEALARM_CONFIG_H

class Config {

public:

    virtual void save() = 0;
    virtual bool load() = 0;

    float cutoffVoltage = 3.1;
    char cutoffDirection = '<';
    float pVoltageInterference = 0.0;
    float nVoltageInterference = 0.0;
};


#endif //VOLTAGEALARM_CONFIG_H