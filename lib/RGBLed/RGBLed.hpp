#pragma once
#include <Arduino.h>

/**
 * @brief A class to control an RGB LED.
 */
class RGBLed
{
public:
    /**
     * @brief Initializes the RGB LED by setting the specified pins as OUTPUT.
     * @param redPin The pin number for the red component of the RGB LED.
     * @param greenPin The pin number for the green component of the RGB LED.
     * @param bluePin The pin number for the blue component of the RGB LED.
     */
    void init(int redPin, int greenPin, int bluePin);

    /**
     * @brief Tests the RGB LED by gradually increasing its brightness of white.
     * @return true if the test is complete, false otherwise.
     */
    bool test();
    
    /**
     * @brief Set the color of the RGB LED by specifying the intensity of red, green, and blue components.
     * @param red The intensity of the red component (0-255).
     * @param green The intensity of the green component (0-255).
     * @param blue The intensity of the blue component (0-255).
     */
    void setColor(uint8_t red, uint8_t green, uint8_t blue);

private:
    int redPin;
    int greenPin;
    int bluePin;
    int testLED = 0;
    unsigned long startTime = 0;
};