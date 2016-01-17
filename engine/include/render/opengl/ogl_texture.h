#ifndef _OGL_TEXTURE_H_
#define _OGL_TEXTURE_H_
#include <string>
#include <cstdlib>
#include <render/texture.h>
#include "ogl.h"

class ogl_texture : public texture
{
    GLenum _target;
    GLuint _handle;
    size_t _width;
    size_t _height;
public:
    void bind();
    GLuint handle() const;
    GLenum target() const;
    void load_image2d(raw_image& ri, const texparms& parms = texparms());
    void load_tex2d(const std::string& img_file,
                    const texparms& parms = texparms());

     ~ogl_texture();
};

extern GLuint gl_teximage2d(const GLubyte *data,
                            size_t width,
                            size_t height,
                            pixel_fmt_t pixelfmt,
                            const texparms& parms = texparms());
#endif
