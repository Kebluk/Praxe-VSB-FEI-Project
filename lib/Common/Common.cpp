#include "Common.hpp"
#include <Arduino.h>

bool timeElapsed(unsigned long &startTime, unsigned long interval) {
    if (startTime == 0) {
        startTime = millis();
        return false;
    }

    if (millis() - startTime >= interval) {
        startTime = millis();
        return true;
    }

    return false;
}