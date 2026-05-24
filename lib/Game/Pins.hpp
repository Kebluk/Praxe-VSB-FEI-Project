#pragma once

// The older way of #pragma once
// #ifndef PINS_HPP
// #define PINS_HPP

// #endif // PINS_HPP


// RGB
constexpr int RGB_R = 14;
constexpr int RGB_G = 27;
constexpr int RGB_B = 26;

// Buttons
constexpr int BTN_1 = 16;

// Rotary Encoder
constexpr int ENC_CLK = 32;  // Amount of steps
constexpr int ENC_DT = 33;   // Direction of rotation
constexpr int ENC_SW = 25;   // The button
constexpr int ENC_VCC = -1;  // The VCC pin
constexpr int ENC_STEPS = 4;

// OLED Display - I2C
// constexpr int OLED_SDA = 21;
// constexpr int OLED_SCL = 22;