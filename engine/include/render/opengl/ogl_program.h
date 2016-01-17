#ifndef _OGL_PROGRAM_H_
#define _OGL_PROGRAM_H_
#include "ogl.h"
#include <unordered_map>
#include <string>
#include <set>

class ogl_program
{
    GLuint _handle;
    std::unordered_map<GLenum, GLuint> _shader_handles;
    std::unordered_map<std::string, GLuint> _attr_cache;
    std::unordered_map<std::string, GLint> _uniform_cache;
    std::set<GLuint> _enable_attr;

public:
    ogl_program();
    ~ogl_program();

    GLuint handle() const;

    void add_shader(const std::string& sourse, GLenum stype);
    void add_shader(const char *sourse, size_t len, GLenum stype);
    void attach_link();
    void bind();
    GLuint get_attr(const std::string& attr);
    void enable_attr(GLuint handle);
    void enable_attr(const std::string& attr);
    void disable_attr(GLuint handle);
    void disable_attr(const std::string& attr);
    GLint get_uniform(const std::string& u);

    static const ogl_program* get_current();

    void uniform1f(GLint location,
                   GLfloat v0);

    void uniform1f(const std::string& u,
                   GLfloat v0);

    void uniform2f(GLint location,
                   GLfloat v0,
                   GLfloat v1);

    void uniform2f(const std::string& u,
                   GLfloat v0,
                   GLfloat v1);

    void uniform3f(GLint location,
                   GLfloat v0,
                   GLfloat v1,
                   GLfloat v2);

    void uniform3f(const std::string& u,
                   GLfloat v0,
                   GLfloat v1,
                   GLfloat v2);

    void uniform4f(GLint location,
                   GLfloat v0,
                   GLfloat v1,
                   GLfloat v2,
                   GLfloat v3);

    void uniform4f(const std::string& u,
                   GLfloat v0,
                   GLfloat v1,
                   GLfloat v2,
                   GLfloat v3);

    void uniform1i(GLint location,
                   GLint v0);

    void uniform1i(const std::string& u,
                   GLint v0);

    //void uniform2i(GLint location,
    //               GLint v0,
    //               GLint v1);

    //void uniform3i(GLint location,
    //               GLint v0,
    //               GLint v1,
    //               GLint v2);

    //void uniform4i(GLint location,
    //               GLint v0,
    //               GLint v1,
    //               GLint v2,
    //               GLint v3);

    //void uniform1ui(GLint location,
    //                GLuint v0);

    //void uniform2ui(GLint location,
    //                GLint v0,
    //                GLuint v1);

    //void uniform3ui(GLint location,
    //                GLint v0,
    //                GLint v1,
    //                GLuint v2);

    //void uniform4ui(GLint location,
    //                GLint v0,
    //                GLint v1,
    //                GLint v2,
    //                GLuint v3);

    //void uniform1fv(GLint location,
    //                GLsizei count,
    //                const GLfloat *value);

    //void uniform2fv(GLint location,
    //                GLsizei count,
    //                const GLfloat *value);

    void uniform3fv(GLint location,
                    GLsizei count,
                    const GLfloat *value);

    void uniform3fv(const std::string& u,
                    GLsizei count,
                    const GLfloat *value);

    //void uniform4fv(GLint location,
    //                GLsizei count,
    //                const GLfloat *value);

    //void uniform1iv(GLint location,
    //                GLsizei count,
    //                const GLint *value);

    //void uniform2iv(GLint location,
    //                GLsizei count,
    //                const GLint *value);

    //void uniform3iv(GLint location,
    //                GLsizei count,
    //                const GLint *value);

    //void uniform4iv(GLint location,
    //                GLsizei count,
    //                const GLint *value);

    //void uniform1uiv(GLint location,
    //                 GLsizei count,
    //                 const GLuint *value);

    //void uniform2uiv(GLint location,
    //                 GLsizei count,
    //                 const GLuint *value);

    //void uniform3uiv(GLint location,
    //                 GLsizei count,
    //                 const GLuint *value);

    //void uniform4uiv(GLint location,
    //                 GLsizei count,
    //                 const GLuint *value);

    //void uniform_matrix2fv(GLint location,
    //                       GLsizei count,
    //                       GLboolean transpose,
    //                       const GLfloat *value);

    //void uniform_matrix3fv(GLint location,
    //                       GLsizei count,
    //                       GLboolean transpose,
    //                       const GLfloat *value);

    void uniform_matrix4fv(GLint location,
                           GLsizei count,
                           GLboolean transpose,
                           const GLfloat *value);

    void uniform_matrix4fv(const std::string& u,
                           GLsizei count,
                           GLboolean transpose,
                           const GLfloat *value);

    //void uniform_matrix2x3fv(GLint location,
    //                         GLsizei count,
    //                         GLboolean transpose,
    //                         const GLfloat *value);

    //void uniform_matrix3x2fv(GLint location,
    //                         GLsizei count,
    //                         GLboolean transpose,
    //                         const GLfloat *value);

    //void uniform_matrix2x4fv(GLint location,
    //                         GLsizei count,
    //                         GLboolean transpose,
    //                         const GLfloat *value);

    //void uniform_matrix4x2fv(GLint location,
    //                         GLsizei count,
    //                         GLboolean transpose,
    //                         const GLfloat *value);

    //void uniform_matrix3x4fv(GLint location,
    //                         GLsizei count,
    //                         GLboolean transpose,
    //                         const GLfloat *value);

    //void uniform_matrix4x3fv(GLint location,
    //                         GLsizei count,
    //                         GLboolean transpose,
    //                         const GLfloat *value);

};





#endif
