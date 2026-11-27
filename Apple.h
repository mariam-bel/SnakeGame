// Snake.h
#pragma once
#include <SDL3/SDL.h>

class Apple {
public:
    Apple(SDL_Renderer* renderer, const SDL_FRect& rect) : rect{rect} {
        SDL_Surface* surface = SDL_LoadBMP("snake.bmp");
        if (!surface) {
            SDL_Log("Error cargando apple.bmp: %s", SDL_GetError());
            return;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
    }

    ~Apple() {
        if (texture) SDL_DestroyTexture(texture);
    }

    Apple(const Apple&) = delete;
    Apple& operator=(const Apple&) = delete;

    void Move(float posX, float posY) {
        rect.x = posX+50.0f;
        rect.y = posY+50.0f;
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