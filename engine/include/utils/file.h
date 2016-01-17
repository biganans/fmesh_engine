#ifndef _FILE_H_
#define _FILE_H_
#include <string>
#include "str.h"
#if defined(USE_SDL)
#include <SDL2/SDL_filesystem.h>

static inline std::string get_base_path(void)
{
    std::string path = SDL_GetBasePath();
#if defined(WIN32) || defined(_WIN32)
    return dos_to_unix(path);
#else
    return path;
#endif

}

#endif





#endif
