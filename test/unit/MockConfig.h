#ifndef MOCKCONFIG_H
#define MOCKCONFIG_H

#include "Config.h"

class MockConfig : public Config {
public:
    void save() override {
        saved = true;
    }

    bool load() override {
        return loadsOk;
    }

    bool saved;
    bool loadsOk;
};

#endif