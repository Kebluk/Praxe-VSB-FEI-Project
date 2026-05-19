#include "Game.hpp"
#include "OLED.hpp"
#include "Encoder.hpp"
#include "RGBLed.hpp"
#include "Pins.hpp"
#include <Arduino.h>

void Game::init()
{
    Serial.begin(9600);
    Serial.println();

    oled.init();
    led.init(RGB_R, RGB_G, RGB_B);
    encoder.init();

    pinMode(BUT_1, INPUT);
    
    oled.drawMenu();
}

void Game::update()
{
    oled.test();
    led.test();
    encoder.test();
/*
    oled.drawMenu();
    delay(2000);*/


}