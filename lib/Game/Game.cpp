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
        if (oledTested)
        {
            oled.drawPleaseSpinEncoder();
        }
        encoderTested = encoder.test();

        if (oledTested && rgbLedTested && encoderTested)
        {
            testing = false;
            oled.clearDisplay();
            oled.display();
            Serial.println("All components initialized. Starting game...");
        }
        else
        {
            return; // Wait until all tests are complete
        }
    }

    switch (gameState)
    {
    case MENU:
        oled.drawMenu();
        if (digitalRead(BTN_1) == HIGH && (millis() - lastButtonPress > 250)) // 250ms debounce
        {
            lastButtonPress = millis();
            gameState = PLAYING;
        }
        break;
    case PLAYING:
        if (player.hp == C_PLAYER_LIVES_MAX)
        {
            led.setColor(0, 255, 0); // zelená
        }
        if (player.hp <= 0)
        {
            led.setColor(0, 0, 0); // vypnuto
            gameState = GAME_OVER;
            return;
        }

        getInput();

        if (timeElapsed(lastPrintTime, 250))
            Serial.println("Lives: " + String(player.hp) + " Score: " + String(player.score) + " Shield Angle: " + String(player.shieldAngle));

        if (timeElapsed(lastBulletSpawnTime, random(C_BULLET_SPAWN_MIN_MS, C_BULLET_SPAWN_MAX_MS)))
        {
            spawnBullet();
        }

        updateBullets();

        checkCollisions();

        render();
        break;
    case GAME_OVER:
        oled.drawGameOver(player.score);
        if (!waitedAfterGameOver)
        {
            delay(500); // počkej 500 ms před umožněním restartu
            waitedAfterGameOver = true;
        }
        if (digitalRead(BTN_1) == HIGH && (millis() - lastButtonPress > 250)) // 250ms debounce
        {
            lastButtonPress = millis();
            resetGame();
            gameState = MENU;
        }
        break;
    }
}

void Game::getInput()
{
    player.shieldAngle = encoder.readEncoder();
}

void Game::resetGame()
{
    player.hp = C_PLAYER_LIVES_MAX;
    player.score = 0;
    player.shieldAngle = 0;
    lastBulletSpawnTime = 0;
    lastPrintTime = 0;
    waitedAfterGameOver = false;

    for (int i = 0; i < C_BULLETS_MAX; i++)
    {
        bullets[i].active = false;
        bullets[i].waitingForParry = false;
        bullets[i].parryStart = 0;
    }
}

void Game::spawnBullet()
{
    for (int i = 0; i < C_BULLETS_MAX; i++)
    {

        if (bullets[i].active)
            continue;

        Bullet &b = bullets[i];

        int side = random(0, 4);

        float x, y;

        // 0 = top
        if (side == 0)
        {
            x = random(0, C_OLED_WIDTH);
            y = 0;
        }
        // 1 = bottom
        else if (side == 1)
        {
            x = random(0, C_OLED_WIDTH);
            y = C_OLED_HEIGHT - 1;
        }
        // 2 = left
        else if (side == 2)
        {
            x = 0;
            y = random(0, C_OLED_HEIGHT);
        }
        // 3 = right
        else
        {
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
    for (int i = 0; i < C_BULLETS_MAX; i++)
    {

        Bullet &b = bullets[i];

        if (!b.active)
            continue;

        // pohyb
        b.x += b.vx * 1.5f;
        b.y += b.vy * 1.5f;

        // mimo obrazovku -> vypnout
        if (b.x < 0 || b.x > C_OLED_WIDTH ||
            b.y < 0 || b.y > C_OLED_HEIGHT)
        {

            b.active = false;
        }
    }
}

void Game::checkCollisions()
{

    unsigned long now = millis();
    static unsigned long lastButtonPress = 0;
    bool buttonPressed = (digitalRead(BTN_1) == CHANGE) && (now - lastButtonPress > 50); // 50ms debounce
    if (buttonPressed)
    {
        lastButtonPress = now;
    }

    for (int i = 0; i < C_BULLETS_MAX; i++)
    {

        Bullet &b = bullets[i];

        if (!b.active)
            continue;

        // vzdálenost bulletu od hráče
        float dx = b.x - C_PLAYER_X;
        float dy = b.y - C_PLAYER_Y;

        float dist = sqrt(dx * dx + dy * dy);

        // mimo dosah štítu → nic se neděje
        if (dist > C_SHIELD_RADIUS + 3) // +3 tolerance
            continue;

        // úhel bulletu vůči středu
        float bulletAngle = atan2(dy, dx) * 180.0f / PI;
        if (bulletAngle < 0)
            bulletAngle += 360.0f;

        // rozdíl vůči štítu
        float diff = fabs(bulletAngle - player.shieldAngle);
        if (diff > 180.0f)
            diff = 360.0f - diff;

        // Odražení štítem
        if ((dist < C_SHIELD_RADIUS + 3 && dist > C_SHIELD_RADIUS - 3) && diff <= C_SHIELD_HALF_ANGLE + 3) // +3 tolerance
        {
            player.score += C_SCORE_PER_HIT;
            b.active = false; // zničená kulka
            b.waitingForParry = false;
            continue;
        }

        // Začátek hit okna, když kulka dorazí ke štítu
        if (!b.waitingForParry)
        {
            b.waitingForParry = true;
            b.parryStart = now;
        }

        // Stiskl včas (jen kdyz kulka dorazi k hraci)
        if (dist <= C_PLAYER_RADIUS + 1 && buttonPressed && (now - b.parryStart <= C_HIT_WINDOW_MS)) // +1 tolerance
        {
            buttonPressed = false; // reset button state after processing
            player.score += C_SCORE_PER_HIT;
            b.active = false;
            b.waitingForParry = false;
            continue;
        }

        // Nestiskl včas → zásah hráče
        if (dist <= C_PLAYER_RADIUS + 1 && (now - b.parryStart > C_HIT_WINDOW_MS)) // +1 tolerance
        {
            player.hp--;

            switch (player.hp)
            {
            case 2:
                led.setColor(255, 255, 0); // žlutá
                break;
            case 1:
                led.setColor(255, 0, 0); // červená
                break;
            }

            b.active = false;
            b.waitingForParry = false;
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