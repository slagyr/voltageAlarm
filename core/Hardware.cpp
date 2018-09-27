#include "Hardware.h"

void Hardware::printValue(char *label, int value) {
    print(label);
    print(value);
    print("\n");
}

void Hardware::println(const char *value) {
    print(value);
    print("\n");
}

void Hardware::println(int value) {
    print(value);
    print("\n");
}


