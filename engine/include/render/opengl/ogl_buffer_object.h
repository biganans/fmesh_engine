#ifndef _OGL_BUFFER_OBJECT_H_
#define _OGL_BUFFER_OBJECT_H_
#include "ogl.h"

class ogl_buffer_object {
    GLenum _target;
    GLuint _handle;
    void *_raw_data = NULL;
    void *_map_data = NULL;
    ogl_buffer_object();
    bool _storage = false;
public:

    GLenum target() const;
    GLuint handle() const;

    explicit ogl_buffer_object(GLenum target);
    ~ogl_buffer_object();

    void bind();

    //不需要bind既可使用
    void data(GLsizeiptr size, const GLvoid *data, GLenum usage = GL_STATIC_DRAW);
    void dynamic_data(GLsizeiptr size, const GLvoid *data);
    //NOTE: glBufferStorage | glNamedBufferStorage
    void data_storage(GLsizeiptr size, const GLvoid *data,
                      GLbitfield flags = GL_MAP_READ_BIT|GL_MAP_WRITE_BIT|GL_MAP_PERSISTENT_BIT|GL_MAP_COHERENT_BIT);

    void* map_data();
    void* map(GLenum access = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
    void flush_map_range(GLintptr offset, GLsizeiptr len);
    bool unmap();

    static void clear_bind();
};


#endif
