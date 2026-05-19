#pragma once

// OLED settings
constexpr int OLED_WIDTH = 128;
constexpr int OLED_HEIGHT = 64;

// Bullet settings
constexpr int MAX_BULLETS = 5;
constexpr int BULLET_SPEED_PER_STEP_MS = 250;
constexpr int BULLET_SPAWN_MIN_MS = 500;
constexpr int BULLET_SPAWN_MAX_MS = 3000;

// Gameplay
constexpr int MAX_LIVES = 3;
constexpr int HIT_WINDOW_MS = 200;
constexpr int SCORE_PER_HIT = 1;