#include <render/renderer.h>
#include <render/opengl/ogl_renderer.h>

renderer *g_renderer;

renderer* renderer::alloc(enum renderer::type t)
{
    if (t == renderer::type::GL) {
        return new ogl_renderer();
    }

    return NULL;
}
