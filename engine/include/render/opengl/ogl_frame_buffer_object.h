#ifndef _OGL_FRAME_BUFFER_OBJECT_H_
#define _OGL_FRAME_BUFFER_OBJECT_H_

#include "ogl.h"
#include <vector>

class ogl_frame_buffer_object
{
    GLuint _handle;
    GLenum _target;
    std::vector<GLuint> _texs;
    ogl_frame_buffer_object();
public:
    explicit ogl_frame_buffer_object(GLenum target);
    ~ogl_frame_buffer_object();
    void attach_texture(GLenum attachment, GLuint texture, GLint level = 0);
    void bind();
};


#endif
