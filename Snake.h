// Snake.h
#pragma once
#include <SDL3/SDL.h>

class Snake {
public:
    Snake(SDL_Renderer* renderer, const SDL_FRect& rect) : rect{rect} {
        SDL_Surface* surface = SDL_LoadBMP("snake.bmp");
        if (!surface) {
            SDL_Log("Error cargando snake.bmp: %s", SDL_GetError());
            return;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
    }

    ~Snake() {
        if (texture) SDL_DestroyTexture(texture);
    }

    Snake(const Snake&) = delete;
    Snake& operator=(const Snake&) = delete;

    void Move(float deltaX, float deltaY) {
        rect.x += deltaX;
        rect.y += deltaY;
    }

    void Render(SDL_Renderer* renderer) const {
        if (texture) SDL_RenderTexture(renderer, texture, nullptr, &rect);
    }

    void KeepInsideWindow(float width, float height) {
        if (rect.x < 0.0f) rect.x = 0.0f;
        if (rect.y < 0.0f) rect.y = 0.0f;
        if (rect.x + rect.w > width)  rect.x = width - rect.w;
        if (rect.y + rect.h > height) rect.y = height - rect.h;
    }

private:
    SDL_FRect rect;
    SDL_Texture* texture = nullptr;
};