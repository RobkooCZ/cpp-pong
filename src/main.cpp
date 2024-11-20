#include <windows.h>
#include "Window.h"

int main() {
    // Initialize and run the game window
    HINSTANCE hInstance = GetModuleHandle(nullptr);  // Get application instance
    int nCmdShow = SW_SHOWNORMAL;                    // Show window normally
    Window window(hInstance, SW_SHOWNORMAL);         // Create and initialize the game window
    window.Run();                                    // Start the game loop
    return 0;
}