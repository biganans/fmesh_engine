#include <render/opengl/ogl_texture.h>
#include <utils/log.h>

static void _tex2d_filter()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

static void _tex2d_repeat()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

static void tex_params(GLenum target, const texparms& parms)
{
    GLint f, w;

    switch (parms.filter) {
        case texfilter::linear:
            f = GL_LINEAR;
            break;
        case texfilter::nearest:
            f = GL_NEAREST;
        default:
            break;
    }

    switch (parms.warp) {
        case texwarp::repeat:
            w = GL_REPEAT;
            break;
        case texwarp::clamp_to_edge:
            w = GL_CLAMP_TO_EDGE;
            break;
        case texwarp::mirrored_repeat:
            w = GL_MIRRORED_REPEAT;
        default:
            break;
    }


    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, f);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, f);
    glTexParameterf(target, GL_TEXTURE_WRAP_S, w);
    glTexParameterf(target, GL_TEXTURE_WRAP_T, w);
}

GLuint gl_teximage2d(const GLubyte *data, size_t width, size_t height, pixel_fmt_t pixelfmt, const texparms& parms)
{
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    tex_params(GL_TEXTURE_2D, parms);

    switch(pixelfmt) {
    case KTEX2D_RGBA8888:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        break;

    case KTEX2D_RGBA4444:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, data);
        break;

    case KTEX2D_RGBA5551:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, data);
        break;

    case KTEX2D_RGB565:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, data);
        break;

    case KTEX2D_RGB888:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        break;

    case KTEX2D_L8:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
        break;

    case KTEX2D_A8:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
        break;

    case KTEX2D_LA88:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
        break;

    case KTEX2D_BGR888:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
        break;

    case KTEX2D_BGR24:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
        break;

    default:
        break;
    }

    return tex;
}


void ogl_texture::bind()
{
    glBindTexture(this->_target, this->_handle);
}


GLuint ogl_texture::handle() const
{
    return this->_handle;
}

GLenum ogl_texture::target() const
{
    return this->_target;
}

void ogl_texture::load_image2d(raw_image& ri,
                               const texparms& parms)
{
    this->_width = ri.width();
    this->_height = ri.height();
    this->_handle = gl_teximage2d((const GLubyte*)ri.data(),
                                  this->_width,
                                  this->_height,
                                  ri.fmt(),
                                  parms);
    this->_target = GL_TEXTURE_2D;
}

void ogl_texture::load_tex2d(const std::string& img_file,
                             const texparms& parms)
{
    raw_image ri(img_file);
    this->_width = ri.width();
    this->_height = ri.height();
    this->_handle = gl_teximage2d((const GLubyte*)ri.data(),
                                  this->_width,
                                  this->_height,
                                  ri.fmt(),
                                  parms);
    this->_target = GL_TEXTURE_2D;
}



ogl_texture::~ogl_texture()
{
    glDeleteTextures(1, &this->_handle);
}
