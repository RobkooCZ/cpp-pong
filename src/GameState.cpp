#include "GameState.h"

GameState::GameState()
    : leftPaddleY(200), rightPaddleY(200),
      ballX(400), ballY(300), ballSpeedX(5), ballSpeedY(5),
      leftScore(0), rightScore(0) {}

void GameState::resetBall() {
    ballX = 400;
    ballY = 300;
    ballSpeedX = -ballSpeedX;  // Reverse ball direction
}