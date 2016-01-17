#ifndef _OGL_FUNC_H_
#define _OGL_FUNC_H_
#include "ogl.h"
#include <utils/log.h>
#include <string>

//GL_ARB_shading_language_include

#define GLSL_VERSION_NUM glsl_version(GL_VERSION_NUM)

#if defined(USE_GLEW)
#define support_instanced_arrays \
    (GLEW_VERSION_3_3 || GLEW_ARB_instanced_arrays)

#define support_texture_storage \
    (GLEW_VERSION_4_2 || GLEW_ARB_texture_storage)

#define support_base_instance \
    (GLEW_VERSION_4_2 || GLEW_ARB_base_instance)

#define support_buffer_storage (GLEW_VERSION_4_4 || GLEW_ARB_buffer_storage)

#define support_separate_shader_objects \
    (GLEW_VERSION_4_1 || GLEW_ARB_separate_shader_objects)

#define support_draw_indirect (GLEW_VERSION_4_0 || GLEW_ARB_draw_indirect)
#define support_direct_state_access \
    (GLEW_VERSION_4_5 || GLEW_ARB_direct_state_access || GLEW_EXT_direct_state_access)

#endif

static inline void vertex_attrib_divisor(GLuint index, GLuint divisor)
{
#if GL_SYS_TYPE == GL_PROFILE_TYPE && defined(USE_GLEW)
    if (GLEW_VERSION_3_3) {
        glVertexAttribDivisor(index, divisor);
    } else {
        if (GLEW_ARB_instanced_arrays) {
            glVertexAttribDivisorARB(index, divisor);
        } else {
            console::error("no divisor support");
            exit(-1);
            //TODO EXT
        }
    }
#endif
}

static inline void draw_arrays_instanced(GLenum mode,
                                         GLint first,
                                         GLsizei count,
                                         GLsizei primcount)
{
#if GL_SYS_TYPE == GL_PROFILE_TYPE && defined(USE_GLEW)
    if (GLEW_VERSION_3_2) {
        glDrawArraysInstanced(mode, first, count, primcount);
    } else {
        if (GLEW_ARB_instanced_arrays) {
            glDrawArraysInstancedARB(mode, first, count, primcount);
        } else {
            console::error("no instanced support");
            exit(-1);
            //TODO EXT
        }
    }
#endif
}


static inline void draw_arrays_instanced_base(GLenum mode,
                                              GLint first,
                                              GLsizei count,
                                              GLsizei primcount,
                                              GLuint baseinstance)
{
#if GL_SYS_TYPE == GL_PROFILE_TYPE && defined(USE_GLEW)
    if (GLEW_VERSION_4_2 || GLEW_ARB_base_instance) {
        glDrawArraysInstancedBaseInstance(mode, first, count, primcount, baseinstance);
    }
#endif
}

typedef struct {
    GLuint  count;
    GLuint  primCount;
    GLuint  first;
    GLuint  baseInstance;
} DrawArraysIndirectCommand;

static inline void draw_arrays_indirect(GLenum mode,
                                        const void *indirect)
{
#if GL_SYS_TYPE == GL_PROFILE_TYPE && defined(USE_GLEW)
    if (GLEW_VERSION_4_0 || GLEW_ARB_draw_indirect) {
        if (!GLEW_VERSION_4_2) {
            const DrawArraysIndirectCommand *cmd = (const DrawArraysIndirectCommand *)indirect;
            if (cmd->baseInstance != 0) {
                console::error("The baseInstance member of the DrawArraysIndirectCommand "
                               "structure is defined only if the GL version is 4.2 or greater. "
                               "For versions of the GL less than 4.2, this parameter is present but is reserved and should be set to zero. "
                               "On earlier versions of the GL, behavior is undefined if it is non-zero.");
                exit(-1);
            }
        }
        glDrawArraysIndirect(mode, indirect);
    }

#endif
}


static inline void draw_elements_instanced(GLenum mode,
                                           GLsizei count,
                                           GLenum type,
                                           const void* indices,
                                           GLsizei primcount)
{
#if GL_SYS_TYPE == GL_PROFILE_TYPE && defined(USE_GLEW)
    if (GLEW_VERSION_3_2) {
        glDrawElementsInstanced(mode, count, type, indices, primcount);
    } else {
        if (GLEW_ARB_instanced_arrays) {
            glDrawElementsInstancedARB(mode, count, type, indices, primcount);
        } else {
            console::error("no instanced support");
            exit(-1);
            //TODO EXT
        }
    }
#endif
}


typedef struct {
    GLuint  count;
    GLuint  primCount;
    GLuint  firstIndex;
    GLuint  baseVertex;
    GLuint  baseInstance;
} DrawElementsIndirectCommand;

static inline void draw_elements_indirect(GLenum mode, GLenum type, const void* indirect)
{
#if GL_SYS_TYPE == GL_PROFILE_TYPE && defined(USE_GLEW)
    if (GLEW_VERSION_4_0 || GLEW_ARB_draw_indirect) {
        if (!GLEW_VERSION_4_2) {
            const DrawElementsIndirectCommand *cmd  = (const DrawElementsIndirectCommand *)indirect;
            if (cmd->baseInstance != 0) {
                console::error("The baseInstance member of the DrawElementsIndirectCommand "
                               "structure is defined only if the GL version is 4.2 or greater. "
                               "For versions of the GL less than 4.2, this parameter is present but is reserved and should be set to zero. "
                               "On earlier versions of the GL, behavior is undefined if it is non-zero.");
                exit(-1);
            }
        }
        glDrawElementsIndirect(mode, type, indirect);
    }
#endif
}

static inline void tex_storage2d(GLenum target,
                                 GLsizei levels,
                                 GLenum internalformat,
                                 GLsizei width,
                                 GLsizei height)
{
#if GL_SYS_TYPE == GL_PROFILE_TYPE && defined(USE_GLEW)
    if (GLEW_VERSION_4_2 || GLEW_ARB_texture_storage) {
        glTexStorage2D(target, levels, internalformat, width, height);
    } else {
        console::error("no glTexStorage2d and GL_ARB_texture_storage support");
        exit(-1);
        //TODO EXT
    }
#endif
}

static inline void tex_storage3d(GLenum target,
                                 GLsizei levels,
                                 GLenum internalformat,
                                 GLsizei width,
                                 GLsizei height,
                                 GLsizei depth)
{
#if GL_SYS_TYPE == GL_PROFILE_TYPE && defined(USE_GLEW)
    if (GLEW_VERSION_4_2 || GLEW_ARB_texture_storage) {
        glTexStorage3D(target, levels, internalformat, width, height, depth);
    } else {
        console::error("no glTexStorage3d and GL_ARB_texture_storage support");
        exit(-1);
        //TODO EXT
    }
#endif
}

static inline void texture_storage2d(GLuint texture,
                                     GLsizei levels,
                                     GLenum internalformat,
                                     GLsizei width,
                                     GLsizei height)
{
#if GL_SYS_TYPE == GL_PROFILE_TYPE && defined(USE_GLEW)
    if (GLEW_VERSION_4_5 || GLEW_ARB_direct_state_access) {
        glTextureStorage2D(texture, levels, internalformat, width, height);
    }
#endif
}

static inline void texture_storage3d(GLuint texture,
                                     GLsizei levels,
                                     GLenum internalformat,
                                     GLsizei width,
                                     GLsizei height,
                                     GLsizei depth)
{
#if GL_SYS_TYPE == GL_PROFILE_TYPE && defined(USE_GLEW)
    if (GLEW_VERSION_4_5 || GLEW_ARB_direct_state_access) {
        glTextureStorage3D(texture, levels, internalformat, width, height, depth);
    }
#endif
}


static inline int glsl_version(int ogl_version)
{
    if (ogl_version >= 330) return ogl_version;

    int v = 100;
    switch (ogl_version) {
    case 200:
        v = 110;
        break;
    case 210:
        v = 120;
        break;
    case 300:
        v = 130;
        break;
    case 310:
        v = 140;
        break;
    case 320:
        v = 150;
        break;
    }

    return v;
}

static inline void ogl_check_error()
{
    GLenum code = glGetError();
    if (code == GL_NO_ERROR) return;

    std::string str;

    switch(code) {
    case GL_INVALID_VALUE:
        str = "GL_INVALID_VALUE";
        break;
    case GL_INVALID_ENUM:
        str = "GL_INVALID_ENUM";
        break;
    case GL_INVALID_OPERATION:
        str = "GL_INVALID_OPERATION";
        break;
    case GL_OUT_OF_MEMORY:
        str = "GL_OUT_OF_MEMORY";
        break;
    }

    console::error("%s", str.c_str());
}

#endif
