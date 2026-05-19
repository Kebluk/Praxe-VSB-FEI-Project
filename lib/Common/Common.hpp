#pragma once

/**
 * @brief Checks if a specified amount of time has elapsed since the last check.
 * @param startTime A reference to the timestamp of the last check.
 * @param interval The interval in milliseconds to check against.
 * @return true if the interval has elapsed, false otherwise.
 */
bool timeElapsed(unsigned long &startTime, unsigned long interval);