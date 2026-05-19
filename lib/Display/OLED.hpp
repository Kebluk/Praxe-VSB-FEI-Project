#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
class OLED
{
public:
    void init();
    void test();
    void clear();
    void drawMenu();
    void drawPlayer(int x, int y);
    void drawBullet(int x, int y);
    void drawScore(int score);
    void drawWin();
    void drawGameOver(int score);
    void render();
    private:
    unsigned long startTime = 0;
    bool isTested = false;
    Adafruit_SSD1306 display;
};