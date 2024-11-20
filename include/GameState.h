#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
public:
    int leftPaddleY;
    int rightPaddleY;
    int ballX, ballY;
    int ballSpeedX, ballSpeedY;
    int leftScore, rightScore;

    GameState();
    void resetBall();  // Reset ball position and reverse direction
};

#endif