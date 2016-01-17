#ifndef _OGL_VERTEX_ARRAY_OBJECT_H_
#define _OGL_VERTEX_ARRAY_OBJECT_H_
#include "ogl.h"


class ogl_vertex_array_object {
    GLuint _handle;
public:
    ogl_vertex_array_object();
    ~ogl_vertex_array_object();
    void bind();
    void bind_divisor();
    void bind_attr();
    void vertex_buffer();
    void vertex_buffers();
    void element_buffer();
};


#endif
