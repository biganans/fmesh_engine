#include <render/opengl/ogl_sysinfo.h>
#include <render/opengl/ogl.h>
#include <cstring>
#include <cctype>

using namespace std;

ogl_sysinfo::ogl_sysinfo()
{
    this->get_sys_info();
    this->get_ext_info();
}


bool ogl_sysinfo::has_ext(const std::string& extname) const
{
    return this->_ext_infos.find(extname) != this->_ext_infos.end();
}


void ogl_sysinfo::get_ext_info()
{
#if (GL_MAJOR < 3)
    const GLubyte* ext_str = glGetString(GL_EXTENSIONS);
    int len = strlen((const char*)ext_str);

    std::string tmp;
    for (int i = 0; i < len; ++i) {
        char c = ext_str[i];
        if (!isspace(c)) {
            tmp += c;
        } else {
            if (!tmp.empty()) {
                this->_ext_infos.insert(tmp);
                tmp.clear();
            }
        }
    }
#else
    GLint n;
    glGetIntegerv(GL_NUM_EXTENSIONS, &n);
    for (int i = 0; i < n; ++i) {
        this->_ext_infos.insert((const char*)glGetStringi(GL_EXTENSIONS, i));
    }
#endif
}


void ogl_sysinfo::get_sys_info()
{
    this->_renderer = (const char*)glGetString(GL_RENDER);
    this->_vendor = (const char*)glGetString(GL_VENDOR);
    this->_version = (const char*)glGetString(GL_VERSION);
#if (GL_MAJOR >= 2)
    this->_shader_version = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
#endif
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &this->_max_tex_units);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &this->_max_tex_size);
}
