#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_
#include "texture.h"
#include <utils/singleton.h>
#include <string>
#include <unordered_map>

class texture_manager
{
    std::unordered_map<std::string, texture*>  _tex_pools;
public:
    void add_tex2d(const std::string& file,
                   const texparms& parms = texparms());

    texture* get(const std::string& file);
};

typedef singleton<texture_manager> g_texture_manager;


#endif
