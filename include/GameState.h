#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Hitboxes.h"

class GameState {
public:
    int leftPaddleY;
    int rightPaddleY;
    int ballX, ballY;
    int ballSpeedX, ballSpeedY;
    int leftScore, rightScore;
    Hitbox leftPaddleHitbox;
    Hitbox rightPaddleHitbox;
    Hitbox ballHitbox;

    GameState();
    void resetBall();  // Reset ball position and reverse direction
};

#endif