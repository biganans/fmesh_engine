#ifndef _LOG_H_
#define _LOG_H_
#include <cassert>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>

#if defined(_MSC_VER)
#define snprintf _snprintf
#include <Windows.h>
#endif

#define UASSERT(cond, str)                              \
    do {                                                \
        if (!cond) {                                    \
            fprintf(stderr, "%s => %s\n",#cond, str);   \
            assert(0);                                  \
        }                                               \
    } while (0)

static const int kBufferSize = 16384;
class console {
    static void print(const char* _string)
    {
#if defined(_MSC_VER)
        OutputDebugString(_string);
#else
        printf("%s", _string);
#endif
    }
public:
    static void debug(const char* _fmt, ...)
    {
        char buff[kBufferSize],
            finalBuff[kBufferSize];
        va_list args;
        va_start(args, _fmt);
        vsnprintf(buff, sizeof(buff), _fmt, args);
        va_end(args);
        snprintf(finalBuff, sizeof(finalBuff), "Debug: %s\n", buff);
        console::print(finalBuff);
    }

    static void log(const char* _fmt, ...)
    {
        char buff[kBufferSize],
            finalBuff[kBufferSize];
        va_list args;
        va_start(args, _fmt);
        vsnprintf(buff, sizeof(buff), _fmt, args);
        va_end(args);
        snprintf(finalBuff, sizeof(finalBuff), "Log: %s\n", buff);
        console::print(finalBuff);
    }

    static void warn(const char* _fmt, ...)
    {
        char buff[kBufferSize],
            finalBuff[kBufferSize];
        va_list args;
        va_start(args, _fmt);
        vsnprintf(buff, sizeof(buff), _fmt, args);
        va_end(args);
        snprintf(finalBuff, sizeof(finalBuff), "Warning: %s\n", buff);
        console::print(finalBuff);
    }

    static void error(const char* _fmt, ...)
    {
        char buff[kBufferSize],
            finalBuff[kBufferSize];
        va_list args;
        va_start(args, _fmt);
        vsnprintf(buff, sizeof(buff), _fmt, args);
        va_end(args);
        snprintf(finalBuff, sizeof(finalBuff), "Error: %s\n", buff);
        console::print(finalBuff);
    }
};

#endif
