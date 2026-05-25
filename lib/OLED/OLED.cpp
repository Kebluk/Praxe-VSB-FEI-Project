#include <SPI.h>
#include <Wire.h>
#include "OLED.hpp"
#include "Config.hpp"
#include "Common.hpp"
#include <Arduino.h>

/**
 * @brief Gets the width of a line of text when rendered on the display.
 * @param display The display object to use for measuring the text.
 * @param text The text to measure.
 * @return The width of the text in pixels.
 */
static uint16_t getLineWidth(Adafruit_SSD1306 &display, const char *text)
{
    int16_t x1 = 0;
    int16_t y1 = 0;
    uint16_t w = 0;
    uint16_t h = 0;
    display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    return w;
}

/**
 * @brief Draws a single line of text centered horizontally at a specific y-coordinate.
 * @param display The display object to draw on.
 * @param text The text to draw.
 * @param y The y-coordinate at which to draw the text. The text will be centered horizontally at this y-coordinate.
 */
static void drawCenteredLineAtY(Adafruit_SSD1306 &display, const char *text, int16_t y)
{
    uint16_t lineWidth = getLineWidth(display, text);
    int16_t startX = (display.width() - (int16_t)lineWidth) / 2;
    display.setCursor(startX, y);
    display.print(text);
}

/**
 * @brief Draws multiple lines of text centered both horizontally and vertically on the display.
 * @param display The display object to draw on.
 * @param lines An array of strings, each representing a line of text to draw.
 * @param lineCount The number of lines in the lines array.
 * @param textSize The size of the text. Each line's height will be 8 pixels multiplied by this text size.
 */
static void drawCenteredLines(Adafruit_SSD1306 &display, const char *const *lines, int lineCount, int textSize)
{
    int16_t displayWidth = display.width();
    int16_t displayHeight = display.height();
    int16_t lineHeight = 8 * textSize;
    int16_t totalHeight = lineCount * lineHeight;
    int16_t startY = (displayHeight - totalHeight) / 2;

    for (int i = 0; i < lineCount; i++)
    {
        uint16_t lineWidth = getLineWidth(display, lines[i]);
        int16_t startX = (displayWidth - (int16_t)lineWidth) / 2;
        display.setCursor(startX, startY + i * lineHeight);
        display.print(lines[i]);
    }
}

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
    int textSize = 1;
    displayObj.setTextSize(textSize);
    displayObj.setTextColor(SSD1306_WHITE);
    const char *lines[] = {"Press button", "to start"};
    drawCenteredLines(displayObj, lines, 2, textSize);
    displayObj.display();
}

void OLED::drawGameOver(int score)
{
    displayObj.clearDisplay();
    int textSize = 1;
    displayObj.setTextSize(textSize);
    displayObj.setTextColor(SSD1306_WHITE);
    String scoreLine = "Score: " + String(score);
    const char *lines[] = {"Game Over", scoreLine.c_str()};
    drawCenteredLines(displayObj, lines, 2, textSize);
    int16_t lineHeight = 8 * textSize;
    int16_t bottomStartY = displayObj.height() - (2 * lineHeight);
    drawCenteredLineAtY(displayObj, "Press button", bottomStartY);
    drawCenteredLineAtY(displayObj, "to restart", bottomStartY + lineHeight);
    displayObj.display();
}

void OLED::drawPlayer()
{
    displayObj.fillCircle(C_PLAYER_X, C_PLAYER_Y, 3, SSD1306_WHITE);
}

void OLED::drawPleaseSpinEncoder()
{
    displayObj.clearDisplay();
    int textSize = 1;
    displayObj.setTextSize(textSize);
    displayObj.setTextColor(SSD1306_WHITE);
    const char *lines[] = {"Please spin", "the encoder", "to test it"};
    drawCenteredLines(displayObj, lines, 3, textSize);
    displayObj.display();
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
}

void OLED::drawBullets(Bullet bullets[])
{
    for (int i = 0; i < C_BULLETS_MAX; i++) {

        if (!bullets[i].active)
            continue;

        int x = (int)bullets[i].x;
        int y = (int)bullets[i].y;
        displayObj.fillRect(x, y, 2, 2, SSD1306_WHITE);
    }
}