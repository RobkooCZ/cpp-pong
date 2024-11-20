#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>
#include "GameState.h"

class Renderer {
public:
    Renderer() {}
    void render(HDC hdc, const GameState& gameState);  // Draw game elements
};

#endif