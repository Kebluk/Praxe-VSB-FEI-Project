#pragma once
#include "AiEsp32RotaryEncoder.h"

class Encoder
{
public:
    /**
     * @brief Initializes the encoder and sets up the ISR. This method must be called before using the encoder. It configures the encoder pins, sets boundaries, and attaches the ISR for handling encoder changes.
     */
    void init();
    /**
     * @brief Tests the encoder by checking for any changes in the encoder's position. This method should be called repeatedly until it returns true, indicating that the encoder is properly initialized and responsive.
     * @return true if the encoder has registered a change (indicating it's working), false otherwise.
     */
    bool test();
    /**
     * @brief Reads the current position of the encoder and returns it as a long integer. The value is multiplied by 40 to scale it according to the encoder's steps.
     * @return The current position of the encoder, scaled by a factor of 40.
     */
    long readEncoder();
private:
    AiEsp32RotaryEncoder encoder;
    static Encoder *instance; // Static pointer for ISR access

    friend void readEncoderISR(); // Allow ISR to access private members
};