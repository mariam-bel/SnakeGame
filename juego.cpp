#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]){
	SDL_Window *window = nullptr;
	SDL_Surface *surface = nullptr;
	SDL_Surface *imageSurface = nullptr;
	SDL_Renderer* renderer = nullptr;
    SDL_Texture* spriteTexture = nullptr;

	float spriteSpeed = 200.0f;

	float speedSenseX = 0;
	float speedSenseY = 0;

	bool running = true;



	if(SDL_Init(SDL_INIT_VIDEO)<0)
		SDL_Log("Video Initialization Error: %s", SDL_GetError());
	
	if(!SDL_CreateWindowAndRenderer( 800, 600, 0, &window, &renderer))
		SDL_Log("Failed to create window and renderer! %s", SDL_GetError());

	
		// Window created
		surface = SDL_GetWindowSurface(window);
		imageSurface = SDL_LoadBMP("fondo.bmp");
		spriteTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

		if (!imageSurface)
			SDL_Log("Image surface loading error: %s", SDL_GetError());

		if(!spriteTexture) 
			SDL_Log("Sprite texture creation error: %s", SDL_GetError());


			SDL_BlitSurface(imageSurface, NULL, surface, NULL);
			SDL_UpdateWindowSurface(window);

			SDL_FRect spriteRect = {
				100.0f,
				100.0f,
				static_cast<float>(imageSurface->w),
				static_cast<float>(imageSurface->h)
			};

			Uint64 lastTime = SDL_GetPerformanceCounter();

			while(running) {
				SDL_Event event;
				while (SDL_PollEvent(&event)) {
					if(event.type == SDL_QUIT) {
						running = false;
					}
				}

				Uint64 currentTime = SDL_GetPerformanceCounter();
				float deltaTime = (currentTime - lastTime) / (float)SDL_GetPerformanceFrequency();

				const Uint8* keyState = SDL_GetKeyboardState(nullptr);

				if(keyState[SDL_SCANCODE_W]) {
					spriteRect.y -= spriteSpeed * deltaTime;
				}
				if(keyState[SDL_SCANCODE_S]) {
					spriteRect.y += spriteSpeed * deltaTime;
				}
				if(keyState[SDL_SCANCODE_A]) {
					spriteRect.x -= spriteSpeed * deltaTime;
				}
				if(keyState[SDL_SCANCODE_D]) {
					spriteRect.x += spriteSpeed * deltaTime;
				}

				if(spriteRect.x < 0.0f) spriteRect.x = 0.0f;
				if(spriteRect.y < 0.0f) spriteRect.y = 0.0f;
				if(spriteRect.x + spriteRect.w > 800.0f) spriteRect.x = 800.0f - spriteRect.w;
				if(spriteRect.y + spriteRect.h > 600.0f) spriteRect.y = 600.0f - spriteRect.h;

				SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
				SDL_RenderClear(renderer);

				SDL_RenderCopyF(renderer, spriteTexture, nullptr, &spriteRect);

				SDL_RenderPresent(renderer);

			


			SDL_Delay(2000);
			
		
	}


	SDL_FreeSurface(imageSurface);
	imageSurface = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	surface = nullptr;
	SDL_Quit();

	return 0;
}
