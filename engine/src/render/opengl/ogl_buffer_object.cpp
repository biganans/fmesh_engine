#include <render/opengl/ogl_buffer_object.h>

ogl_buffer_object::ogl_buffer_object(GLenum target):_target(target)
{
    glGenBuffers(1, &this->_handle);
}

ogl_buffer_object::~ogl_buffer_object()
{

    if (this->_map_data != NULL) {
#if GL_CORE_DSA
        glUnmapNamedBuffer(this->_handle);
#else
        this->bind();
        glUnmapBuffer(this->_target);
#endif
    }

    glDeleteBuffers(1, &this->_handle);
}

GLenum ogl_buffer_object::target() const
{
    return this->_target;
}
GLuint ogl_buffer_object::handle() const
{
    return this->_handle;
}



static ogl_buffer_object *__current_bind_buffer = NULL;
void ogl_buffer_object::bind()
{
    if (__current_bind_buffer == this) return;
    glBindBuffer(this->_target, this->_handle);
    __current_bind_buffer = this;
}

void ogl_buffer_object::clear_bind()
{
    __current_bind_buffer = NULL;
}

void ogl_buffer_object::data(GLsizeiptr size, const GLvoid *data, GLenum usage)
{
#if GL_CORE_DSA
    glNamedBufferData(this->_handle, size, data, usage);
#else
    this->bind();
    glBufferData(this->_target, size, data, usage);
#endif
    this->_raw_data = (void*)data;
    this->_storage = false;
}

void ogl_buffer_object::data_storage(GLsizeiptr size, const GLvoid *data, GLbitfield flags)
{
#if GL_CORE_DSA
    glNamedBufferStorage(this->_handle, (GLsizei)size, data, flags);
    this->_map_data = glMapNamedBufferRange(this->_handle, 0, (GLsizei)size, flags);
#elif GL_BUFFER_STORAGE
    this->bind();
    glBufferStorage(this->_target, size, data, flags);
    this->_map_data = glMapBufferRange(this->_target, 0, size, flags);
#endif
    this->_raw_data = (void*)data;
    this->_storage = true;
}

void ogl_buffer_object::dynamic_data(GLsizeiptr size, const GLvoid *data)
{
#if GL_BUFFER_STORAGE
    if (GLEW_ARB_buffer_storage) {
        this->data_storage(size, data);
        return;
    }
#endif
    this->data(size, data, GL_DYNAMIC_DRAW);
}

void* ogl_buffer_object::map_data()
{
    return this->_map_data;
}

void* ogl_buffer_object::map(GLenum access)
{

    if (this->_map_data == NULL) {
#if GL_CORE_DSA
        this->_map_data = glMapNamedBuffer(this->_handle, access);
#else
        this->bind();
        this->_map_data = glMapBuffer(this->_target, access);
#endif
    }

    return this->_map_data;
}

bool ogl_buffer_object::unmap()
{
    bool re = true;
    if (!this->_storage) {
        re = glUnmapBuffer(this->_target);
        this->_map_data = NULL;
    }
    return re;
}
