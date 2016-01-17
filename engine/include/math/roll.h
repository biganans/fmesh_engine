#ifndef _ROLL_H_
#define _ROLL_H_

#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

static inline unsigned int urandom(void)
{
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64) //HACK: std::random_device BUG in MinGW!
    static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 mt(seed);
#else
    std::random_device rd;
    std::mt19937 mt(rd());
#endif
    return mt();
}

//1d6 2d6 1d10
typedef unsigned int (*randfunc)(void);

static inline std::vector<int> roll(const std::string& rule, randfunc rfunc = urandom)
{
    int count = 1;
    int dt;

    std::vector<int> v;
    std::string s;

    for (int i = 0; i < rule.size(); ++i) {
        char c = rule.at(i);

        if (isdigit(c)) {
            s += c;
            continue;
        }

        if (tolower(c) == 'd') {
            if (!s.empty()) {
                count = std::max(1, atoi(s.c_str()));
                s.clear();
            }
            continue;
        }

        std::cerr << "ERROR: exp error" << std::endl;
        return v;
    }

    dt = atoi(s.c_str());

    for (int i = 0; i < count; ++i) {
        v.push_back(rfunc() % dt + 1);
    }

    return v;
}

#endif
