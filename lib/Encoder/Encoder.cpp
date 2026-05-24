#include <Arduino.h>
#include "Pins.hpp"
#include "Encoder.hpp"

// Static member initialization
Encoder* Encoder::instance = nullptr;

// ISR function with IRAM_ATTR for ESP32
void IRAM_ATTR readEncoderISR()
{
    if (Encoder::instance != nullptr)
    {
        Encoder::instance->encoder.readEncoder_ISR();
    }
}

void Encoder::init()
{
    Encoder::instance = this;  // Set static pointer to this instance
    
    encoder = AiEsp32RotaryEncoder(ENC_CLK, ENC_DT, ENC_SW, ENC_VCC, ENC_STEPS, false);
    encoder.begin();
    encoder.setup(readEncoderISR);
    encoder.setBoundaries(0, 35, true);
    encoder.setAcceleration(0);
    Serial.println("Encoder initialized");
}

bool Encoder::test()
{
    // Read the encoder value
    if (encoder.encoderChanged())
    {
        Serial.println(encoder.readEncoder());
        //encoder.setEncoderValue(0);
    }

    // Check for button presses
    if (encoder.isEncoderButtonClicked())
    {
        Serial.println("Encoder initialized");
        return true;  // Test complete when button is pressed
    }
    return false;  // Test not yet complete
}

long Encoder::readEncoder()
{
    return encoder.readEncoder();
}