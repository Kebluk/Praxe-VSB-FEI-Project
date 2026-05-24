#pragma once
#include "Config.hpp"

struct Player {
    int shieldAngle = 0;

    int hp = C_PLAYER_LIVES_MAX;
    int score = 0;
};