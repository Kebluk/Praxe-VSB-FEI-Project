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
    Player player;
    Bullet bullets[C_BULLETS_MAX];
    Encoder encoder;
    bool encoderTested = false;
    OLED oled;
    bool oledTested = false;
    RGBLed led;
    bool rgbLedTested = false;
    bool testing = true;
    unsigned long lastBulletSpawnTime = 0;
    void getInput();
    void spawnBullet();
    void updateBullets();
    void checkCollisions();
    void render();
};