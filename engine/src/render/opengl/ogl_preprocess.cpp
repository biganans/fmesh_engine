#include <render/opengl/ogl_preprocess.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <utils/str.h>
#include <utils/log.h>

#if defined(USE_PCRE)
#define PCRE_STATIC
#include <pcrecpp.h>
#else
#include <regex>
#endif


const std::string& ogl_preprocess::sources() const
{
    return this->_sources;
}

void ogl_preprocess::add_define(const std::string& name, const std::string& value)
{
    this->_defines.insert(std::make_pair(name, value));
}

void ogl_preprocess::add_decl(const std::string& str)
{
    this->_decls.push_back(str);
}

void ogl_preprocess::parse(const std::string& file, std::string& sources)
{
    std::ifstream fin(file.c_str());
    if (!fin) {
        console::error("unknown %s", file.c_str());
        exit(-1);
    }

    std::string s;
#if defined(USE_PCRE)
    pcrecpp::RE re("^[ \t]*#[ \t]*include[ \t]*\"([^\"<>]*)\"");

    while (getline(fin, s)) {
	std::string inc_file;
	re.FullMatch(s, &inc_file);
        if (!inc_file.empty()) {
            auto ite = this->_import_ref.find(inc_file);
            if (ite == this->_import_ref.end()) {
                this->_import_ref.insert(inc_file);
                this->parse(this->_base_path + inc_file, sources);
            }
        } else {
            sources = sources + s + "\n";
        }
    }

#else
    std::regex inc_regex("^[ \t]*#[ \t]*include[ \t]*\"([^\"<>]*)\"");
    std::smatch inc_match;
    while (getline(fin, s)) {
        if (std::regex_match(s, inc_match, inc_regex)) {
            std::string inc_file = inc_match[1].str();
            auto ite = this->_import_ref.find(inc_file);
            if (ite == this->_import_ref.end()) {
                this->_import_ref.insert(inc_file);
                this->parse(this->_base_path + inc_file, sources);
            }
        } else {
            sources = sources + s + "\n";
        }
    }
#endif
    fin.close();
}


static inline std::string fmt_define(const std::string& name, const std::string& value)
{
    return "#define " + name + " " + value + "\n";
}

int ogl_preprocess::exec(const std::string& file)
{
    if (file.empty()) return -1;
    this->_import_ref.clear();
    this->_sources.clear();

    if (!this->_defines.empty()) {
        for (auto ite = this->_defines.begin(); ite != this->_defines.end(); ++ite) {
            this->_sources = this->_sources + fmt_define(ite->first, ite->second);
        }
    }

    if (!this->_decls.empty()) {
        for (auto ite = this->_decls.begin(); ite != this->_decls.end(); ++ite) {
            this->_sources = this->_sources + (*ite) + "\n";
        }
    }

    this->_base_path = substr_path(file);

    this->parse(file, this->_sources);
    return 0;
}
