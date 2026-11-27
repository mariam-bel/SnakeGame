#include <iostream>
#include <SDL3/SDL.h>

#include "Snake.h"
#include "Apple.h"

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* backgroundTexture = nullptr;
    SDL_Surface* backgroundSurface = nullptr;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Video initialization error: %s", SDL_GetError());
        return 1;
    }

    if (!SDL_CreateWindowAndRenderer(
            "Snake Game", 800, 600, 0, &window, &renderer)) {
        SDL_Log("Failed to create window and renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    backgroundSurface = SDL_LoadBMP("fondo.bmp");
    if (!backgroundSurface) {
        SDL_Log("Image surface loading error: %s", SDL_GetError());
    } else {
        backgroundTexture =
            SDL_CreateTextureFromSurface(renderer, backgroundSurface);
        SDL_DestroySurface(backgroundSurface);

        if (!backgroundTexture) {
            SDL_Log("Sprite texture creation error: %s", SDL_GetError());
        }
    }


    Snake snake{renderer, SDL_FRect{100.0f, 100.0f, 50.0f, 50.0f}};
    Apple apple{renderer, SDL_FRect{200.0f, 200.0f, 50.0f, 50.0f}};
    constexpr float spriteSpeed = 200.0f;
    bool running = true;
    Uint64 lastTime = SDL_GetPerformanceCounter();

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        const Uint64 currentTime = SDL_GetPerformanceCounter();
        const float deltaTime =
            static_cast<float>(currentTime - lastTime) /
            static_cast<float>(SDL_GetPerformanceFrequency());
        lastTime = currentTime;

        int keyCount = 0;
        const bool* keyState = SDL_GetKeyboardState(&keyCount);

        if (keyCount > SDL_SCANCODE_W && keyState[SDL_SCANCODE_W]) {
            snake.Move(0.0f, -spriteSpeed * deltaTime);
        }
        if (keyCount > SDL_SCANCODE_S && keyState[SDL_SCANCODE_S]) {
            snake.Move(0.0f, spriteSpeed * deltaTime);
        }
        if (keyCount > SDL_SCANCODE_A && keyState[SDL_SCANCODE_A]) {
            snake.Move(-spriteSpeed * deltaTime, 0.0f);
        }
        if (keyCount > SDL_SCANCODE_D && keyState[SDL_SCANCODE_D]) {
            snake.Move(spriteSpeed * deltaTime, 0.0f);
        }
        snake.KeepInsideWindow(800.0f, 600.0f);

        float posX = snake.GetX();
        float posY = snake.GetY();
        
        apple.Move(posX, posY);
        apple.KeepInsideWindow(800.0f, 600.0f);
        


        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        if (backgroundTexture) {
            SDL_RenderTexture(renderer, backgroundTexture, nullptr, nullptr);
        }

        snake.Render(renderer);
        apple.Render(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
