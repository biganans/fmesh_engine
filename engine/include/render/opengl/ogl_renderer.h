#ifndef _OGL_RENDERER_H_
#define _OGL_RENDERER_H_
#include <set>
#include <math/maths.h>
#include <render/renderer.h>
#include "ogl.h"

class renderer;

class ogl_renderer : public renderer
{
    std::set<enum render_enable_cap> _enable_cache;
    vec4 _color;
    GLenum _polygon_mode = GL_FILL;
protected:
    void polygon_mode(GLenum mode); //GL_FILL GL_LINE NOTE:with no support for ES
public:
    ogl_renderer();
    enum renderer::type type() const;
    void viewport(int x, int y, int w, int h);
    void clear_color(float r, float g, float b, float a);
    void clear();
    void draw(double dt);

    void enable(enum render_enable_cap cap);
    void disable(enum render_enable_cap cap);
};

#endif
