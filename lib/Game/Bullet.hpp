#pragma once

struct Bullet {
    float x;
    float y;

    float vx;
    float vy;

    bool active = false;

    bool waitingForParry = false;
    unsigned long parryStart = 0;
};