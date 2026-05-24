#pragma once

// OLED settings
constexpr int C_OLED_WIDTH = 128;
constexpr int C_OLED_HEIGHT = 64;

// Bullet settings
constexpr int C_BULLETS_MAX = 5;
constexpr int C_BULLET_SPEED_PER_STEP_MIN_MS = 300;
constexpr int C_BULLET_SPEED_PER_STEP_MAX_MS = 500;
constexpr int C_BULLET_SPAWN_MIN_MS = 500;
constexpr int C_BULLET_SPAWN_MAX_MS = 1500;

// Player settings
constexpr int C_PLAYER_X = 64;
constexpr int C_PLAYER_Y = 32;
constexpr int C_PLAYER_RADIUS = 3;
constexpr int C_PLAYER_LIVES_MAX = 3;

// Shield settings
constexpr int C_SHIELD_RADIUS = 14;
constexpr int C_SHIELD_HALF_ANGLE = 30;

// Game settings
constexpr int C_HIT_WINDOW_MS = 250;
constexpr int C_SCORE_PER_HIT = 1;