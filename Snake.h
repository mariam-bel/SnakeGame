#pragma once
#include <SDL3/SDL.h>

class Snake {
public:
    explicit Snake(const SDL_FRect& rect)
        : rect{rect} {}

    void Move(float deltaX, float deltaY) {
        rect.x += deltaX;
        rect.y += deltaY;
    }

    void Render(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    void KeepInsideWindow(float width, float height) {
        if (rect.x < 0.0f) rect.x = 0.0f;
        if (rect.y < 0.0f) rect.y = 0.0f;
        if (rect.x + rect.w > width) rect.x = width - rect.w;
        if (rect.y + rect.h > height) rect.y = height - rect.h;
    }

private:
    SDL_FRect rect;
};