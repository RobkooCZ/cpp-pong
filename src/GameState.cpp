#include "GameState.h"
#include "Constants.h"

GameState::GameState()
    : leftPaddleY(YRES / 2 - PADDLE_HEIGHT / 2),
      rightPaddleY(YRES / 2 - PADDLE_HEIGHT / 2),
      ballX(XRES / 2 + BALL_SIZE),
      ballY(YRES / 2 + BALL_SIZE),
      ballSpeedX(5),
      ballSpeedY(5),
      leftScore(0),
      rightScore(0),
      leftPaddleHitbox{
          PADDLE_DISTANCE_FROM_EDGE,  // x1: left edge of paddle 
          leftPaddleY,                // y1: top edge of the paddle
          PADDLE_DISTANCE_FROM_EDGE + PADDLE_WIDTH,               // x2: right edge of paddle
          leftPaddleY + PADDLE_HEIGHT // y2: bottom edge of paddle
      },
      rightPaddleHitbox{
            XRES - PADDLE_WIDTH - PADDLE_DISTANCE_FROM_EDGE,        // x1: left edge of paddle
            rightPaddleY,               // y1: top edge of the paddle
            XRES - PADDLE_DISTANCE_FROM_EDGE,                       // x2: right edge of paddle
            rightPaddleY + PADDLE_HEIGHT// y2: bottom edge of paddle
        },
      ballHitbox{
            ballX - BALL_SIZE,           // x1: left edge of ball
            ballY - BALL_SIZE,           // y1: top edge of ball
            ballX + BALL_SIZE,           // x2: right edge of ball
            ballY + BALL_SIZE            // y2: bottom edge of ball
      } {}

void GameState::resetBall() {
    ballX = XRES/2 + BALL_SIZE;
    ballY = YRES/2 + BALL_SIZE;
    ballSpeedX = -ballSpeedX;  // Reverse ball direction
}