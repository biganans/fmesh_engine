#ifndef _OGL_SYSINFO_H_
#define _OGL_SYSINFO_H_
#include <set>
#include <string>
#include <utils/singleton.h>
#include <utils/meta.h>
class ogl_sysinfo
{
    std::set<std::string> _ext_infos;

    void get_ext_info();
    void get_sys_info();
public:
    ogl_sysinfo();
    $property_readonly(std::string, shader_version);
    $property_readonly(std::string, version);
    $property_readonly(std::string, vendor);
    $property_readonly(std::string, renderer);
    $property_readonly_copy(int, max_tex_units);
    $property_readonly_copy(int, max_tex_size);
    bool has_ext(const std::string& extname) const;
};
#endif
