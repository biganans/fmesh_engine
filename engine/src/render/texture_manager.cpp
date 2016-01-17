#include <render/texture_manager.h>

void texture_manager::add_tex2d(const std::string &file,
                                const texparms &parms)
{
    if (this->_tex_pools.find(file) == this->_tex_pools.end()) {
        texture *tex = texture::alloc();
        tex->load_tex2d(file, parms);
        this->_tex_pools.insert(std::make_pair(file, tex));
    }
}


texture* texture_manager::get(const std::string& file)
{
    if (this->_tex_pools.find(file) != this->_tex_pools.end()) {
        return this->_tex_pools[file];
    }

    return NULL;
}
