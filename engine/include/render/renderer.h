#ifndef _RENDERER_H_
#define _RENDERER_H_

enum render_enable_cap {
    texture_2d,
    cull_face,
    blend,
    dither,
    stencil_test,
    depth_test,
    scissor_test,
    polygon_offset_fill,
    sample_alpha_to_coverage,
    sample_coverage
};

class renderer
{
public:
    enum type {
        GL,
        GLES,
        DX11,
        DX12
    };

    virtual enum renderer::type type() const = 0;
    virtual void viewport(int x, int y, int w, int h) = 0;
    virtual void clear_color(float r, float g, float b, float a) = 0;
    virtual void clear() = 0;
    virtual void draw(double dt) = 0;
    virtual ~renderer(){}
    static renderer* alloc(enum renderer::type t);
};

extern renderer *g_renderer;

#endif
