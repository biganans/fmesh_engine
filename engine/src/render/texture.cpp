#include <render/texture.h>
#include <render/renderer.h>
#include <render/opengl/ogl_texture.h>
#include <cassert>
texture* texture::alloc()
{
    assert(g_renderer);
    if (g_renderer->type() == renderer::type::GL ||
        g_renderer->type() == renderer::type::GLES) {
        return new ogl_texture();
    } else {
        return NULL;
    }
}
