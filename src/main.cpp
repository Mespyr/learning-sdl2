#include <iostream>
#include <SDL2/SDL.h>
#include "include/util.h"
#include "include/cleanup.h"
#include "include/texture.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

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

	std::string image_path = get_res_path() + "background.bmp";
	SDL_Texture *tex = load_texture(image_path, ren);
	if (tex == nullptr)
	{
		cleanup(tex, ren, window);
		SDL_Quit();
		return 1;
	}

	for (int i = 0; i < 3; ++i)
	{
		SDL_RenderClear(ren);

		int w, h;
		SDL_QueryTexture(tex, NULL, NULL, &w, &h);
		render_texture(tex, ren, 0, 0);
		render_texture(tex, ren, w, 0);
		render_texture(tex, ren, 0, h);
		render_texture(tex, ren, w, h);

		SDL_RenderPresent(ren);
		SDL_Delay(1000);
	}

	cleanup(tex, ren, window);
	SDL_Quit();
	return 0;
}
