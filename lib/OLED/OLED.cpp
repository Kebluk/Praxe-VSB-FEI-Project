#include <SPI.h>
#include <Wire.h>
#include "OLED.hpp"
#include "Config.hpp"
#include "Common.hpp"
#include <Arduino.h>

void OLED::init()
{
    if (!displayObj.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
}

bool OLED::test()
{
    if (isTested)
    {
        return true;
    }

    displayObj.fillScreen(SSD1306_WHITE);
    displayObj.display();
    if (timeElapsed(startTime, 1500))
    {
        displayObj.clearDisplay();
        displayObj.display();
        isTested = true;
        Serial.println("OLED initialized");
        return true;
    }
    return false;
}

void OLED::clearDisplay()
{
    displayObj.clearDisplay();
}

void OLED::display()
{
    displayObj.display();
}

void OLED::drawMenu()
{
    displayObj.clearDisplay();

    displayObj.drawPixel(0, 0, SSD1306_WHITE);
    displayObj.drawPixel(5, 63, SSD1306_WHITE);
    displayObj.drawPixel(10, 62, SSD1306_WHITE);
    displayObj.drawPixel(127, 0, SSD1306_WHITE);
    displayObj.drawPixel(127, 63, SSD1306_WHITE);

    displayObj.drawRect(0, 0, 128, 64, SSD1306_WHITE);
    displayObj.drawRect(1, 1, 126, 62, SSD1306_BLACK);

    // Player
    displayObj.fillRect(63, 31, 2, 2, SSD1306_WHITE);

    displayObj.drawCircle(63, 31, 11, SSD1306_WHITE);
    displayObj.drawCircle(64, 31, 11, SSD1306_WHITE);
    displayObj.drawCircle(63, 32, 11, SSD1306_WHITE);
    displayObj.drawCircle(64, 32, 11, SSD1306_WHITE);

    displayObj.display();

    // display.drawPixel(64, 32, SSD1306_WHITE);
    /*displayObj.drawPixel(127, 0, SSD1306_WHITE);
    displayObj.drawPixel(0, 62, SSD1306_WHITE);*/

    /*Serial.println("Width: " + String(displayObj.width()));
    Serial.println("Height: " + String(displayObj.height()));

    displayObj.drawPixel(64, 32, SSD1306_WHITE);

    displayObj.drawCircle(64, 32, 20, SSD1306_WHITE);*/

    /*displayObj.setTextSize(1);
    displayObj.setTextColor(SSD1306_WHITE);
    displayObj.setCursor(0, 10);
    displayObj.println("Press button to start");*/
}

void OLED::drawPlayer()
{
    displayObj.fillCircle(C_PLAYER_X, C_PLAYER_Y, 3, SSD1306_WHITE);
}

void OLED::drawShield(int angle)
{
    int prevX = 0;
    int prevY = 0;

    bool first = true;

    for (int a = -C_SHIELD_HALF_ANGLE; a <= C_SHIELD_HALF_ANGLE; a += 3)
    {

        float rad = (angle + a) * DEG_TO_RAD;

        int x = C_PLAYER_X + cos(rad) * C_SHIELD_RADIUS;

        int y = C_PLAYER_Y + sin(rad) * C_SHIELD_RADIUS;

        if (!first)
            displayObj.drawLine(prevX, prevY, x, y, SSD1306_WHITE);

        prevX = x;
        prevY = y;

        first = false;
    }
    /*
    int cx = C_PLAYER_X;
    int cy = C_PLAYER_Y;

    int prevX = 0;
    int prevY = 0;

    for (int a = -C_SHIELD_HALF_ANGLE; a <= C_SHIELD_HALF_ANGLE; a += 3)
    {

        float rad = (angle + a) * DEG_TO_RAD;

        int x = cx + cos(rad) * C_SHIELD_RADIUS;
        int y = cy + sin(rad) * C_SHIELD_RADIUS;

        if (a != -C_SHIELD_HALF_ANGLE)
        {
            displayObj.drawLine(prevX, prevY, x, y, SSD1306_WHITE);
        }

        prevX = x;
        prevY = y;
    }*/
}

void OLED::drawBullets(Bullet bullets[])
{
    for (int i = 0; i < C_BULLETS_MAX; i++) {

        if (!bullets[i].active)
            continue;

        displayObj.drawPixel((int)bullets[i].x, (int)bullets[i].y, SSD1306_WHITE);
    }
}