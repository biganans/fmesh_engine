#ifndef _SDL2_VIEW_H_
#define _SDL2_VIEW_H_
#include <SDL2/SDL.h>
#include <string>

class sdl2_view
{
public:
    void create_context(int width, int height, const std::string& name);
    void quit();
    void toggle_full_screen();
    void handle_key_event(SDL_Keysym *keysym);
    void handle_events();
    void sdldie(const char *msg);
    void check_sdl_error(int line = -1);
    void swap();
private:
    int screen_width;
    int screen_height;
    SDL_Window *mainwindow;
    SDL_GLContext maincontext;
    bool windowed;
    bool windowOK;
};

#endif
