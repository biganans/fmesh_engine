#ifndef _STR_H_
#define _STR_H_

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include "log.h"

#define STRINGIFY(A) #A

static inline std::string substr_path(const std::string& file)
{
    std::string base_path = "";
    size_t pos = file.find_last_of('/');
    if (pos != std::string::npos) {
        base_path = file.substr(0, pos + 1);
    }

    return base_path;
}


static inline std::string substr_file(const std::string& file)
{
    std::string fn = "";
    size_t pos = file.find_last_of('/');
    if (pos != std::string::npos) {
        fn = file.substr(pos + 1, file.length());
    } else {
        fn = file;
    }

    return fn;
}

static inline std::string& ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}


static inline std::string& rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

static inline std::string& trim(std::string &s)
{
    return ltrim(rtrim(s));
}


static inline std::vector<std::string> split(const std::string& str, const std::string& pattern)
{
    std::vector<std::string> v;
    size_t len = pattern.length();
    size_t pos = 0;
    size_t begin = 0;

    while ((pos = str.find(pattern, begin)) != -1) {
        std::string t = str.substr(begin, pos - begin);
        v.push_back(t);
        begin = pos + len;
    }

    v.push_back(str.substr(begin, str.length() - begin));

    return v;
}

static inline std::string& operator>>(std::stringstream& ss, std::string& str)
{
    str = ss.str();
    return str;
}

template<typename T>
static inline std::string to_string(const T& v)
{
    std::stringstream ss;
    ss << v;
    return ss.str();
}


template <typename T, typename T2>
static inline T cast_to(const T2& from)
{
    std::stringstream ss;
    T to;
    ss << from;
    ss >> to;
    return to;
}


template<typename T>
static inline void print_bit(T c)
{
    char _bi = 1;
    for (int i = sizeof(T) * 8 - 1; i >= 0; --i) {
        if (c & (_bi << i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

static inline bool u8_is_ascii(char c)
{
    return !(c & (1 << 7));
}

static inline bool u8_is_noascii_char(char c)
{
    return !((c >> 6 & 0x3) ^ 0x2);
}

static inline int u8_is_noascii_head(char c)
{
    if (!((c >> 5 & 0x7) ^ 0x6)) return 2;
    if (!((c >> 4 & 0xF) ^ 0xE)) return 3;
    if (!((c >> 3 & 0x1F) ^ 0x1E)) return 4;
    return 0;
}

static inline size_t u8_len(const std::string& str)
{
    int _index = 0;
    for (int i = 0; i < str.size();) {
        char c = str.at(i);
        int size = u8_is_noascii_head(c);
        if (size > 0) {
            i += size;
        } else if (u8_is_ascii(c)) {
            ++i;
        } else {
            console::error("invalid utf-8 charactre");
            return -1;
        }

        ++_index;
    }

    return _index;
}


static inline std::string u8_at(const std::string& str, int index)
{
    std::string t;
    int _index = 0;
    for (int i = 0; i < str.size();) {
        char c = str.at(i);
        int size = u8_is_noascii_head(c);
        if (size > 0) {
            if (_index == index) {
                t.assign(str.begin() + i, str.begin() + i + size);
                goto quit;
            } else {
                i += size;
                ++_index;
            }
            continue;
        } else if (u8_is_ascii(c)) {
            if (_index == index) {
                t = std::string(1, c);
                goto quit;
            } else {
                ++_index;
            }
        } else {
            console::error("invalid utf-8 charactre");
            goto quit;
        }
        ++i;
    }

  overflow:
    console::error("buffer overflow");
    exit(-1);

  quit:
    return t;
}


static inline std::vector<std::string> u8_each_split(const std::string& str)
{
    std::vector<std::string> re;
    std::string t;
    for (int i = 0; i < str.size();) {
        char c = str.at(i);
        int size = u8_is_noascii_head(c);
        if (size > 0) {
            t.clear();
            t.assign(str.begin() + i, str.begin() + i + size);
            i += size;
            re.push_back(t);
            continue;
        } else if (u8_is_ascii(c)) {
            re.push_back(std::string(1, c));
        } else {
            console::error("invalid utf-8 charactre");
            goto quit;
        }
        ++i;
    }
  quit:
    return re;
}

static inline std::string dos_to_unix(const std::string& path)
{
    std::string wp;

    for (int i = 0; i < path.size(); ++i) {
        char c = path.at(i);
        if (c == '\\') {
            wp += '/';
            continue;
        }
        wp += c;
    }

    return wp;
}

static inline std::string path_join(const std::string& origin,
                                    const std::string& path)
{
    std::string uo = dos_to_unix(origin);
    std::string up = dos_to_unix(path);
    std::string r = uo;
    if (uo.back() != '/') {
        r += '/';
    }

    if (up.front() == '/') {
        r += up.substr(1);
    } else {
        r += up;
    }
    return r;
}

#endif


