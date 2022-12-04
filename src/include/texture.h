#ifndef TEXTURE_H 
#define TEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "util.h"

SDL_Texture* load_texture(const std::string &file, SDL_Renderer* ren);
void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

#endif
