#include <render/opengl/ogl_frame_buffer_object.h>



ogl_frame_buffer_object::ogl_frame_buffer_object(GLenum target)
    :_target(target)
{
    glGenFramebuffers(1, &this->_handle);
}


ogl_frame_buffer_object::~ogl_frame_buffer_object()
{
    glDeleteFramebuffers(1, &this->_handle);
    if (!this->_texs.empty()) {
        glDeleteTextures(this->_texs.size(), this->_texs.data());
    }
}

void ogl_frame_buffer_object::attach_texture(GLenum attachment,
                                             GLuint texture,
                                             GLint level)
{
    glFramebufferTexture(this->_target, attachment, texture, level);
    this->_texs.push_back(texture);
}

void ogl_frame_buffer_object::bind()
{
    glBindFramebuffer(this->_target, this->_handle);
}
