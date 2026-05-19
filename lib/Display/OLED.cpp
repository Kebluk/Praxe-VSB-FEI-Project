#include <SPI.h>
#include <Wire.h>
#include "OLED.hpp"
#include "Config.hpp"
#include "Common.hpp"
#include <Arduino.h>

void OLED::init()
{
    display = Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
    // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
}

void OLED::test()
{
    if (isTested)
    {
        return;
    }

    display.fillScreen(SSD1306_WHITE);
    display.display();
    if (timeElapsed(startTime, 1500))
    {
        clear();
        isTested = true;
        Serial.println("OLED initialized");
    }
}

void OLED::clear()
{
    display.clearDisplay();
    display.display();
}

void OLED::drawMenu()
{
    clear();

    display.drawPixel(0, 0, SSD1306_WHITE);
    display.drawPixel(5, 63, SSD1306_WHITE);
    display.drawPixel(10, 62, SSD1306_WHITE);
    display.drawPixel(127, 0, SSD1306_WHITE);
    display.drawPixel(127, 63, SSD1306_WHITE);

    display.drawRect(0, 0, 128, 64, SSD1306_WHITE);
    display.drawRect(1, 1, 126, 62, SSD1306_BLACK);

    // Player
    display.fillRect(63, 31, 2, 2, SSD1306_WHITE);

    display.drawCircle(63, 31, 11, SSD1306_WHITE);
    display.drawCircle(64, 31, 11, SSD1306_WHITE);
    display.drawCircle(63, 32, 11, SSD1306_WHITE);
    display.drawCircle(64, 32, 11, SSD1306_WHITE);
    
    display.display();

    // display.drawPixel(64, 32, SSD1306_WHITE);
    /*display.drawPixel(127, 0, SSD1306_WHITE);
    display.drawPixel(0, 62, SSD1306_WHITE);*/

    /*Serial.println("Width: " + String(display.width()));
    Serial.println("Height: " + String(display.height()));

    display.drawPixel(64, 32, SSD1306_WHITE);

    display.drawCircle(64, 32, 20, SSD1306_WHITE);*/

    /*display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.println("Press button to start");*/
}