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
    rect = {50, gameState.leftPaddleY, 60, gameState.leftPaddleY + 100};
    FillRect(hdc, &rect, whiteBrush);

    // Right paddle
    rect = {750, gameState.rightPaddleY, 760, gameState.rightPaddleY + 100};
    FillRect(hdc, &rect, whiteBrush);

    // Ball
    Ellipse(hdc, gameState.ballX - 10, gameState.ballY - 10, gameState.ballX + 10, gameState.ballY + 10);

    // Score
    std::string scoreText = std::to_string(gameState.leftScore) + " : " + std::to_string(gameState.rightScore);
    TextOutA(hdc, (XRES / 2) - 50, 20, scoreText.c_str(), scoreText.length());

    DeleteObject(blackBrush);
    DeleteObject(whiteBrush);
}