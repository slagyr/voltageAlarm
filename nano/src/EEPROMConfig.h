#ifndef NANO_EEPROMCONFIG_H
#define NANO_EEPROMCONFIG_H

#include <Config.h>

class EEPROMConfig : public Config {
    void save() override;

    bool load() override;
};


#endif //NANO_EEPROMCONFIG_H
