#ifndef _OGL_PREPROCESS_H_
#define _OGL_PREPROCESS_H_

#include <string>
#include <set>
#include <map>
#include <vector>

class ogl_preprocess
{
    std::set<std::string> _import_ref;
    std::string _sources;
    std::string _base_path;
    std::map<std::string, std::string> _defines;
    std::vector<std::string> _decls;
    void parse(const std::string& file, std::string& sources);
public:
    void add_decl(const std::string& str);
    void add_define(const std::string& name, const std::string& value);
    int exec(const std::string& file);
    const std::string& sources() const;
};



#endif
