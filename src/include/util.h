#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <SDL2/SDL.h>

std::string get_res_path();
void log_sdl_error(std::ostream &os, const std::string &msg);

#endif
