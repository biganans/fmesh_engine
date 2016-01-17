#ifndef _OGL_H_
#define _OGL_H_
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

#define GL_SYS_TYPE 0
#define GL_MAJOR 2
#define GL_MINOR 1

#define GL_PROFILE_TYPE 0
#define GLES_PROFILE_TYPE 1

#if defined(GL_PROFILE_3_2)
#undef GL_MAJOR
#undef GL_MINOR
#define GL_MAJOR 3
#define GL_MINOR 2

#undef GL_SYS_TYPE
#define GL_SYS_TYPE GL_PROFILE_TYPE
#endif

#if defined(GL_PROFILE_3_3)
#undef GL_MAJOR
#undef GL_MINOR
#define GL_MAJOR 3
#define GL_MINOR 3

#undef GL_SYS_TYPE
#define GL_SYS_TYPE GL_PROFILE_TYPE
#endif

#if defined(GL_PROFILE_4_4)
#undef GL_MAJOR
#undef GL_MINOR
#define GL_MAJOR 4
#define GL_MINOR 4

#undef GL_SYS_TYPE
#define GL_SYS_TYPE GL_PROFILE_TYPE
#endif


#if defined(GL_PROFILE_4_5)
#undef GL_MAJOR
#undef GL_MINOR
#define GL_MAJOR 4
#define GL_MINOR 5

#undef GL_SYS_TYPE
#define GL_SYS_TYPE GL_PROFILE_TYPE
#endif

#if defined(USE_GLEW)
#include <GL/glew.h>
static inline void init_glew()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "glew init error\n");
        exit(EXIT_FAILURE);
    }
}

#endif

#define GL_VERSION_NUM (GL_MAJOR * 10 + GL_MINOR) * 10

#define GL_CORE_DSA 0
#define GL_BUFFER_STORAGE 0


#if GL_SYS_TYPE == GL_PROFILE_TYPE && GL_VERSION_NUM >= 450
#undef GL_CORE_DSA
#define GL_CORE_DSA 1
#endif

#if GL_SYS_TYPE == GL_PROFILE_TYPE && GL_VERSION_NUM >= 440
#undef GL_BUFFER_STORAGE
#define GL_BUFFER_STORAGE 1
#endif



#endif
