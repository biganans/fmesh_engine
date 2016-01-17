#include <render/opengl/ogl_vertex_array_object.h>
#include <render/opengl/ogl_func.h>

using namespace std;

ogl_vertex_array_object::ogl_vertex_array_object()
{
    glGenVertexArrays(1, &this->_handle);
}

ogl_vertex_array_object::~ogl_vertex_array_object()
{
    glDeleteVertexArrays(1, &this->_handle);
}

void ogl_vertex_array_object::bind()
{
    glBindVertexArray(this->_handle);
}

void ogl_vertex_array_object::bind_divisor()
{
}

void ogl_vertex_array_object::bind_attr()
{
}

void ogl_vertex_array_object::vertex_buffer()
{
}

void ogl_vertex_array_object::vertex_buffers()
{
}

void ogl_vertex_array_object::element_buffer()
{
}
