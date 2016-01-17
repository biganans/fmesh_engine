#include <render/opengl/ogl_program.h>
#include <render/opengl/ogl_func.h>
#include <utils/log.h>
#include <cstdio>
#include <cstdlib>

static GLuint compile_shader(const char *shader_source, int len, GLenum shader_type)
{
    GLuint shader_handle = glCreateShader(shader_type);

    glShaderSource(shader_handle, 1, &shader_source, &len);
    glCompileShader(shader_handle);

#if defined(DEBUG) || defined(_DEBUG)
    GLint compile_success;
    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_success);

    if (compile_success == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shader_handle, sizeof(messages), 0, &messages[0]);
        console::error("compile shader, %s", messages);
        exit(-1);
    }
#endif

    return shader_handle;
}

ogl_program::ogl_program()
{
}


void ogl_program::attach_link()
{
    GLuint program_handle = glCreateProgram();

    for (auto it = this->_shader_handles.begin();
         it != this->_shader_handles.end(); ++it) {
        glAttachShader(program_handle, it->second);
    }

    glLinkProgram(program_handle);

#if defined(DEBUG) || defined(_DEBUG)
    GLint link_success = GL_FALSE;
    glGetProgramiv(program_handle, GL_LINK_STATUS, &link_success);
    if (link_success == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(program_handle, sizeof(messages), 0, &messages[0]);
        console::error("link shader %s", messages);
        exit(-1);
    }
#endif
//    glUseProgram(program_handle);
    this->_handle = program_handle;
}


GLuint ogl_program::handle() const
{
    return this->_handle;
}


//TODO cache
void ogl_program::add_shader(const char *sourse, size_t len, GLenum stype)
{
    GLuint s = compile_shader(sourse, len, stype);
    this->_shader_handles.insert(std::make_pair(stype, s));
}

void ogl_program::add_shader(const std::string& sourse, GLenum stype)
{
    this->add_shader(sourse.c_str(), sourse.size(), stype);
}

//切换shader状态机开销极大
static ogl_program *__current_use_program = NULL;
void ogl_program::bind()
{
    if (__current_use_program != this) {
        glUseProgram(this->_handle);
        __current_use_program = this;
    }
}


const ogl_program *ogl_program::get_current()
{
    return __current_use_program;
}


void ogl_program::enable_attr(GLuint handle)
{
    auto ite = this->_enable_attr.find(handle);
    if (ite == this->_enable_attr.end()) {
        glEnableVertexAttribArray(handle);
        this->_enable_attr.insert(handle);
    }
}


void ogl_program::enable_attr(const std::string& attr)
{
    this->enable_attr(this->get_attr(attr));
}


void ogl_program::disable_attr(GLuint handle)
{
    auto ite = this->_enable_attr.find(handle);
    if (ite != this->_enable_attr.end()) {
        glDisableVertexAttribArray(handle);
        this->_enable_attr.erase(ite);
    }
}


void ogl_program::disable_attr(const std::string& attr)
{
    this->disable_attr(this->get_attr(attr));
}




GLuint ogl_program::get_attr(const std::string& attr)
{
    if (this->_attr_cache.find(attr) != this->_attr_cache.end()) {
        return this->_attr_cache[attr];
    }

    GLuint handle = glGetAttribLocation(this->_handle, attr.c_str());
    this->_attr_cache[attr] = handle;
    return handle;
}

GLint ogl_program::get_uniform(const std::string& u)
{
    if (this->_uniform_cache.find(u) != this->_uniform_cache.end()) {
        return this->_uniform_cache[u];
    }

    GLint handle = glGetUniformLocation(this->_handle, u.c_str());
    this->_uniform_cache[u] = handle;
    return handle;
}



ogl_program::~ogl_program()
{
    glDeleteProgram(this->_handle);
    for (auto it = this->_shader_handles.begin();
         it != this->_shader_handles.end(); ++it) {
        glDeleteShader(it->second);
    }
}

void ogl_program::uniform1f(GLint location,
                            GLfloat v0)
{
    glProgramUniform1f(this->handle(), location, v0);
}

void ogl_program::uniform1f(const std::string& u,
                            GLfloat v0)
{
    this->uniform1f(this->get_uniform(u), v0);
}


void ogl_program::uniform2f(GLint location,
                            GLfloat v0,
                            GLfloat v1)
{
    glProgramUniform2f(this->handle(), location, v0, v1);
}

void ogl_program::uniform2f(const std::string& u,
                            GLfloat v0,
                            GLfloat v1)
{
    this->uniform2f(this->get_uniform(u), v0, v1);
}


void ogl_program::uniform3f(GLint location,
                            GLfloat v0,
                            GLfloat v1,
                            GLfloat v2)
{
    glProgramUniform3f(this->handle(), location, v0, v1, v2);
}

void ogl_program::uniform3f(const std::string& u,
                            GLfloat v0,
                            GLfloat v1,
                            GLfloat v2)
{
    this->uniform3f(this->get_uniform(u), v0, v1, v2);
}

void ogl_program::uniform4f(GLint location,
                            GLfloat v0,
                            GLfloat v1,
                            GLfloat v2,
                            GLfloat v3)
{
    glProgramUniform4f(this->handle(), location, v0, v1, v2, v3);
}

void ogl_program::uniform4f(const std::string& u,
                            GLfloat v0,
                            GLfloat v1,
                            GLfloat v2,
                            GLfloat v3)
{
    this->uniform4f(this->get_uniform(u), v0, v1, v2, v3);
}

void ogl_program::uniform1i(GLint location,
                            GLint v0)
{
    glProgramUniform1i(this->handle(), location, v0);
}

void ogl_program::uniform1i(const std::string& u,
                            GLint v0)
{
    this->uniform1i(this->get_uniform(u), v0);
}

void ogl_program::uniform3fv(GLint location,
                             GLsizei count,
                             const GLfloat *value)
{
    glProgramUniform3fv(this->handle(), location, count, value);
}

void ogl_program::uniform3fv(const std::string& u,
                             GLsizei count,
                             const GLfloat *value)
{
    this->uniform3fv(this->get_uniform(u), count, value);
}

void ogl_program::uniform_matrix4fv(GLint location,
                                    GLsizei count,
                                    GLboolean transpose,
                                    const GLfloat *value)
{
    glProgramUniformMatrix4fv(this->handle(), location, count, transpose, value);
}

void ogl_program::uniform_matrix4fv(const std::string& u,
                                    GLsizei count,
                                    GLboolean transpose,
                                    const GLfloat *value)
{
    this->uniform_matrix4fv(this->get_uniform(u), count, transpose, value);
}
