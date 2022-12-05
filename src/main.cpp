#include <iostream>
#include <SDL2/SDL.h>
#include "include/util.h"
#include "include/cleanup.h"
#include "include/texture.h"

const int SCREEN_WIDTH  = 700;
const int SCREEN_HEIGHT = 700;

int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		log_sdl_error(std::cout, "SDL_Init");
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Learning SDL", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		log_sdl_error(std::cout, "SDL_CreateWindow");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)
	{
		cleanup(window);
		log_sdl_error(std::cout, "SDL_CreateRenderer");
		SDL_Quit();
		return 1;
	}

	std::string image_path = get_res_path() + "png_test.png";
	SDL_Texture *tex = load_texture(image_path, ren);
	if (tex == nullptr)
	{
		cleanup(tex, ren, window);
		SDL_Quit();
		return 1;
	}

	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
			if (e.type == SDL_KEYDOWN)
				quit = true;
			if (e.type == SDL_MOUSEBUTTONDOWN)
				quit = true;
		}

		SDL_RenderClear(ren);
		render_texture(tex, ren, 0, 0,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		render_texture(tex, ren, SCREEN_WIDTH / 2, 0,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		render_texture(tex, ren, 0, SCREEN_HEIGHT / 2,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		render_texture(tex, ren, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		SDL_RenderPresent(ren);
	}

	cleanup(tex, ren, window);
	SDL_Quit();
	return 0;
}
