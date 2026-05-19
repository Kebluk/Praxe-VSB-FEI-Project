#pragma once
#include "OLED.hpp"
#include "Encoder.hpp"
#include "RGBLed.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Config.hpp"

class Game
{
public:
    /**
     * @brief Initializes the game state.
     */
    void init();

    /**
     * @brief Updates the game state.
     */
    void update();

private:
    Encoder encoder;
    OLED oled;
    RGBLed led;
    Player player;
    Bullet bullets[MAX_BULLETS];
    int lives;
    int score;
};