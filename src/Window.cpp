#include "Window.h"
#include "Constants.h"
#include <iostream>

Window::Window(HINSTANCE hInstance, int nCmdShow) : hInstance(hInstance), nCmdShow(nCmdShow) {
    CreateWindowInstance();
}

Window::~Window() {}

void Window::CreateWindowInstance() {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"PongWindowClass"; // Use L for wide-character strings

    if (!RegisterClass(&wc)) {
        std::cerr << "Failed to register window class!" << std::endl;
        exit(1);
    }

    hwnd = CreateWindowEx(
        0, L"PongWindowClass", L"Pong Game",  // Prefix strings with L
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        XRES, YRES, nullptr, nullptr, hInstance, this);

    if (!hwnd) {
        std::cerr << "Failed to create window!" << std::endl;
        exit(1);
    }

    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    SetTimer(hwnd, TIMER_ID, TIMER_INTERVAL, nullptr);
    ShowWindow(hwnd, nCmdShow);
}
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (window) {
        return window->InstanceWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Window::InstanceWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            renderer.render(hdc, gameState);  // Draw game
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_TIMER:
            if (wParam == TIMER_ID) {
                // Update ball position
                gameState.ballX += gameState.ballSpeedX;
                gameState.ballY += gameState.ballSpeedY;

                // Update hitboxes
                gameState.ballHitbox = {
                    gameState.ballX - BALL_SIZE, gameState.ballY - BALL_SIZE,
                    gameState.ballX + BALL_SIZE, gameState.ballY + BALL_SIZE
                };
                gameState.leftPaddleHitbox = {
                    PADDLE_DISTANCE_FROM_EDGE, gameState.leftPaddleY,
                    PADDLE_DISTANCE_FROM_EDGE + PADDLE_WIDTH, gameState.leftPaddleY + PADDLE_HEIGHT
                };
                gameState.rightPaddleHitbox = {
                    XRES - PADDLE_WIDTH - PADDLE_DISTANCE_FROM_EDGE, gameState.rightPaddleY,
                    XRES - PADDLE_DISTANCE_FROM_EDGE, gameState.rightPaddleY + PADDLE_HEIGHT
                };

                // Ball collision with bottom or top
                if (gameState.ballY <= 0 || gameState.ballY >= YRES - (4 * BALL_SIZE)) {
                    gameState.ballSpeedY = -gameState.ballSpeedY;
                }
                
                // Ball collision with paddles
                if (areHitboxesColliding(gameState.ballHitbox, gameState.leftPaddleHitbox) ||
                    areHitboxesColliding(gameState.ballHitbox, gameState.rightPaddleHitbox)) {
                    gameState.ballSpeedX = -gameState.ballSpeedX;
                }

                // Scoring logic
                if (gameState.ballX <= 0) { gameState.rightScore++; gameState.resetBall(); }
                if (gameState.ballX >= XRES) { gameState.leftScore++; gameState.resetBall(); }

                InvalidateRect(hwnd, nullptr, TRUE);
            }
            return 0;

        case WM_KEYDOWN:
            if (wParam == 'W' && gameState.leftPaddleY > 0) gameState.leftPaddleY -= 25;
            if (wParam == 'S' && gameState.leftPaddleY < YRES - PADDLE_HEIGHT) gameState.leftPaddleY += 25;
            if (wParam == VK_UP && gameState.rightPaddleY > 0) gameState.rightPaddleY -= 25;
            if (wParam == VK_DOWN && gameState.rightPaddleY < YRES - PADDLE_HEIGHT) gameState.rightPaddleY += 25;
            InvalidateRect(hwnd, nullptr, TRUE);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void Window::Run() {
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}