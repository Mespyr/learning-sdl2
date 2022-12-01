#include "include/util.h"

void log_sdl_error(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

std::string get_res_path()
{
	#ifdef _WIN32
	const char PATH_SEP = '\\';
	#else
	const char PATH_SEP = '/';
	#endif

	static std::string base_res;

	if (base_res.empty())
	{
		char *base_path = SDL_GetBasePath();
		if (base_path)
		{
			base_res = base_path;
			SDL_free(base_path);
		}
		else
		{
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		base_res = base_res + "res" + PATH_SEP;
	}
	return base_res;
}
