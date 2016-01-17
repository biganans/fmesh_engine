#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <utils/singleton.h>

struct screen
{
    typedef enum _interface
    {
        interface_portrait = 0,
        interface_portrait_upside_down,
        interface_landscape_left,
        interface_landscape_right,
    } interface_t;

    int width;
    int height;
    interface_t face;
    float scale;
};

typedef singleton<screen> g_screen;


#endif
