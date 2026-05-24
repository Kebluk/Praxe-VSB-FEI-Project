#include "Common.hpp"
#include <Arduino.h>

bool timeElapsed(unsigned long &lastTime, unsigned long interval) {
    if (lastTime == 0) {
        lastTime = millis();
        return false;
    }

    if (millis() - lastTime >= interval) {
        lastTime = millis();
        return true;
    }

    return false;
}