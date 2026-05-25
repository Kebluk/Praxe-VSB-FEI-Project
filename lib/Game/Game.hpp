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
     * @brief Initializes the game state, must be called once before using the game.
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
    bool waitedAfterGameOver = false;
    int gameState = MENU;
    /**
     * @brief Gets input from the encoder and updates the player's position.
     */
    void getInput();
    /**
     * @brief Spawns a new bullet at the player's position.
     */
    void spawnBullet();
    /**
     * @brief Updates the position of all active bullets.
     */
    void updateBullets();
    /**
     * @brief Checks for collisions between bullets and the player.
     */
    void checkCollisions();
    /**
     * @brief Renders the game state on the OLED display.
     */
    void render();
    /**
     * @brief Resets the game state.
     */
    void resetGame();
};