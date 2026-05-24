#include "RGBLed.hpp"
#include "Common.hpp"
#include <Arduino.h>

void RGBLed::init(int redPin, int greenPin, int bluePin)
{
    this->redPin = redPin;
    this->greenPin = greenPin;
    this->bluePin = bluePin;

    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

bool RGBLed::test()
{
    if (testLED > 3)
        return true;

    switch (testLED)
    {
    case 0:
        setColor(255, 0, 0); // Red
        if (timeElapsed(startTime, 500))
        {
            setColor(0, 0, 0);
            testLED++;
        }
        break;
    case 1:
        setColor(0, 255, 0); // Green
        if (timeElapsed(startTime, 500))
        {

            setColor(0, 0, 0);
            testLED++;
        }
        break;
    case 2:
        setColor(0, 0, 255); // Blue
        if (timeElapsed(startTime, 500))
        {
            setColor(0, 0, 0);
            testLED++;
        }
        break;
    default:               // case 3+
        setColor(0, 0, 0); // Turn off the LED
        testLED++;
        Serial.println("RGB LED initialized");
        return true;
    }
    return false;
}

void RGBLed::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
}