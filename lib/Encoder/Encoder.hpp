#pragma once
#include "AiEsp32RotaryEncoder.h"

class Encoder
{
    public:
        void init();
        void test();
    private:
        AiEsp32RotaryEncoder encoder;
        static Encoder* instance;  // Static pointer for ISR access
        
        friend void readEncoderISR();  // Allow ISR to access private members
};