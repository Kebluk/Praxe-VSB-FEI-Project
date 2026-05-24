#pragma once
#include "OLED.hpp"
#include "Encoder.hpp"
#include "RGBLed.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Config.hpp"

enum GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

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
    unsigned long lastPrintTime = 0;
    unsigned long lastButtonPress = 0;
    int gameState = MENU;
    void getInput();
    void spawnBullet();
    void updateBullets();
    void checkCollisions();
    void render();
    void resetGame();
};