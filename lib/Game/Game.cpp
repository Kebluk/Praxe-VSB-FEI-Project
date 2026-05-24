#include "Game.hpp"
#include "OLED.hpp"
#include "Encoder.hpp"
#include "RGBLed.hpp"
#include "Pins.hpp"
#include "Common.hpp"
#include <Arduino.h>

void Game::init()
{
    Serial.begin(9600);
    Serial.println();

    oled.init();
    led.init(RGB_R, RGB_G, RGB_B);
    encoder.init();

    pinMode(BTN_1, INPUT);

    randomSeed(millis());
}

void Game::update()
{
    // During the testing phase, we want to run the tests for OLED, RGB LED, and Encoder. We will only proceed with the game logic once all tests are complete.
    if (testing)
    {
        oledTested = oled.test();
        rgbLedTested = led.test();
        encoderTested = encoder.test();

        if (oledTested && rgbLedTested && encoderTested)
        {
            testing = false;
        }
        else
        {
            return; // Wait until all tests are complete
        }
    }

    Serial.println("Lives: " + String(player.hp) + " Score: " + String(player.score));
    getInput();

    if (timeElapsed(lastBulletSpawnTime, random(C_BULLET_SPAWN_MIN_MS, C_BULLET_SPAWN_MAX_MS)))
    {
        spawnBullet();
        lastBulletSpawnTime = millis();
    }

    updateBullets();

    checkCollisions();

    render();
}

void Game::getInput()
{
    player.shieldAngle = encoder.readEncoder() * 10;
    Serial.print("Shield Angle: ");
    Serial.println(player.shieldAngle);
}

void Game::spawnBullet()
{
    for (int i = 0; i < C_BULLETS_MAX; i++) {

        if (bullets[i].active)
            continue;

        Bullet &b = bullets[i];

        int side = random(0, 4);

        float x, y;

        // 0 = top
        if (side == 0) {
            x = random(0, C_OLED_WIDTH);
            y = 0;
        }
        // 1 = bottom
        else if (side == 1) {
            x = random(0, C_OLED_WIDTH);
            y = C_OLED_HEIGHT - 1;
        }
        // 2 = left
        else if (side == 2) {
            x = 0;
            y = random(0, C_OLED_HEIGHT);
        }
        // 3 = right
        else {
            x = C_OLED_WIDTH - 1;
            y = random(0, C_OLED_HEIGHT);
        }

        b.x = x;
        b.y = y;

        // směr do středu
        float dx = C_PLAYER_X - x;
        float dy = C_PLAYER_Y - y;

        float len = sqrt(dx * dx + dy * dy);

        b.vx = dx / len;
        b.vy = dy / len;

        b.active = true;
        b.waitingForParry = false;

        return;
    }
}

void Game::updateBullets()
{
    for (int i = 0; i < C_BULLETS_MAX; i++) {

        Bullet &b = bullets[i];

        if (!b.active)
            continue;

        // pohyb
        b.x += b.vx * 1.5f;
        b.y += b.vy * 1.5f;

        // mimo obrazovku -> vypnout
        if (b.x < 0 || b.x > C_OLED_WIDTH ||
            b.y < 0 || b.y > C_OLED_HEIGHT) {

            b.active = false;
        }
    }
}

void Game::checkCollisions() {

    unsigned long now = millis();
    static unsigned long lastButtonPress = 0;
    bool buttonPressed = (digitalRead(BTN_1) == HIGH) && (now - lastButtonPress > 50);  // 50ms debounce
    if (buttonPressed) lastButtonPress = now;

    for (int i = 0; i < C_BULLETS_MAX; i++) {

        Bullet &b = bullets[i];

        if (!b.active)
            continue;

        // vzdálenost bulletu od hráče
        float dx = b.x - C_PLAYER_X;
        float dy = b.y - C_PLAYER_Y;

        float dist = sqrt(dx * dx + dy * dy);

        // mimo dosah hráče → nic se neděje
        if (dist > C_PLAYER_RADIUS)
            continue;

        // úhel bulletu vůči středu
        float bulletAngle = atan2(dy, dx) * 180.0f / PI;
        if (bulletAngle < 0) bulletAngle += 360.0f;

        // rozdíl vůči štítu
        float diff = fabs(bulletAngle - player.shieldAngle);
        if (diff > 180.0f)
            diff = 360.0f - diff;

        // Odražení štítem
        if (diff <= C_SHIELD_HALF_ANGLE) {
            b.active = false;   // zničená kulka
            continue;
        }

        // Začátek hit okna
        if (!b.waitingForParry) {
            b.waitingForParry = true;
            b.parryStart = now;
            continue;  // Wait one frame before checking button
        }

        // Stiskl včas
        if (buttonPressed) {
            player.score++;
            b.active = false;
            continue;
        }

        // Nestiskl včas
        if (now - b.parryStart > C_HIT_WINDOW_MS) {
            player.hp--;
            b.active = false;
        }
    }
}

void Game::render()
{
    oled.clearDisplay();

    oled.drawPlayer();

    oled.drawShield(player.shieldAngle);

    oled.drawBullets(bullets);

    oled.display();
}