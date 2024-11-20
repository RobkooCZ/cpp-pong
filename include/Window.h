#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include "GameState.h"
#include "Renderer.h"
#include "Constants.h"

class Window {
private:
    HINSTANCE hInstance;
    HWND hwnd;
    GameState gameState;   // Manage game state (paddles, ball, scores)
    Renderer renderer;     // Manage rendering logic
    int nCmdShow;

    void CreateWindowInstance();       // Setup the window
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT InstanceWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); // Instance-specific message handling

public:
    Window(HINSTANCE hInstance, int nCmdShow);
    ~Window();

    void Run();  // Main game loop
};

#endif