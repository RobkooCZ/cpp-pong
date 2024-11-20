#include "Renderer.h"
#include "Constants.h"
#include <string>

void Renderer::render(HDC hdc, const GameState& gameState) {
    HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
    RECT rect;

    // Background
    rect = {0, 0, XRES, YRES};
    FillRect(hdc, &rect, blackBrush);

    // Left paddle
    rect = {PADDLE_DISTANCE_FROM_EDGE, gameState.leftPaddleY, PADDLE_DISTANCE_FROM_EDGE + PADDLE_WIDTH, gameState.leftPaddleY + PADDLE_HEIGHT};
    FillRect(hdc, &rect, whiteBrush);

    // Right paddle
    rect = {XRES - PADDLE_DISTANCE_FROM_EDGE - PADDLE_WIDTH, gameState.rightPaddleY, XRES - PADDLE_DISTANCE_FROM_EDGE, gameState.rightPaddleY + 100};
    FillRect(hdc, &rect, whiteBrush);

    // Ball
    Ellipse(hdc, gameState.ballX - BALL_SIZE, gameState.ballY - BALL_SIZE, gameState.ballX + BALL_SIZE, gameState.ballY + BALL_SIZE);

    // Score
    std::string scoreText = std::to_string(gameState.leftScore) + " : " + std::to_string(gameState.rightScore);
    TextOutA(hdc, (XRES / 2) - 50, 20, scoreText.c_str(), scoreText.length());

    DeleteObject(blackBrush);
    DeleteObject(whiteBrush);
}