#include <Arduino.h>
#include "Game.hpp"

Game game;

void setup() {
    game.init();
}

void loop() {
    game.update();
} 