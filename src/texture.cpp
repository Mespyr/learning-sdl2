#include "include/texture.h"

SDL_Texture* load_texture(const std::string &file, SDL_Renderer* ren)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface *img = SDL_LoadBMP(file.c_str());

	if (img != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(ren, img);
		SDL_FreeSurface(img);
		if (texture == nullptr)
			log_sdl_error(std::cout, "CreateTextureFromSurface");
	}
	else
		log_sdl_error(std::cout, "LoadBMP");

	return texture;
}

void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
