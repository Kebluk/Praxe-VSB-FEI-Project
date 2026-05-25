#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Bullet.hpp"
#include "Player.hpp"
#include "Config.hpp"

class OLED
{
public:
    void init();
    bool test();
    void display();
    void clearDisplay();
    void drawPlayer();
    void drawShield(int angle);
    void drawBullets(Bullet bullets[]);
    void drawMenu();
    void drawGameOver(int score);
    void drawPleaseSpinEncoder();
    /**
     * @brief Draws a shield around the player with a given angle.
     * @param cx The x-coordinate of the center of the shield.
     * @param cy The y-coordinate of the center of the shield.
     * @param angle The angle of the shield in degrees. The shield will be drawn from (angle - 20) to (angle + 20).
     */
    Adafruit_SSD1306 displayObj = Adafruit_SSD1306(C_OLED_WIDTH, C_OLED_HEIGHT, &Wire, -1);
    private:
    unsigned long startTime = 0;
    bool isTested = false;
};