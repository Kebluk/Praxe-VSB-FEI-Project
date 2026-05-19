#include "Player.hpp"
#include "Config.hpp"

void Player::increaseScore()
{
    score += SCORE_PER_HIT;
}

void Player::decreaseLives()
{
    lives--;
}