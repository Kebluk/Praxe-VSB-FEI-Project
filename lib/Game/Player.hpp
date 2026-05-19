#pragma once

class Player
{
private:
    int x;
    int y;
    int score;
    int lives;

public:
    /**
     * @brief Increases the player's score by a predefined amount.
     */
    void increaseScore();
    
    /**
     * @brief Decreases the player's lives by one.
     */
    void decreaseLives();
};