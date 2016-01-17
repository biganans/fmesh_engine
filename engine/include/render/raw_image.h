#ifndef _RAW_IMAGE_H_
#define _RAW_IMAGE_H_
#include <cstdlib>
#include <string>

typedef enum {
    KTEX2D_RGBA8888,
    KTEX2D_RGBA4444,
    KTEX2D_RGBA5551,
    KTEX2D_RGB565,
    KTEX2D_RGB888,
    KTEX2D_L8,
    KTEX2D_A8,
    KTEX2D_LA88,
    KTEX2D_BGR888,
    KTEX2D_BGR24
} pixel_fmt_t;


#define USE_SDL_IMAGE //test
#if defined(USE_SDL_IMAGE)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
class raw_image_sdl
{
    SDL_Surface *_surface = NULL;
    pixel_fmt_t _type = KTEX2D_RGBA8888;

    void pixel_format();
    raw_image_sdl(const raw_image_sdl& img);
    raw_image_sdl& operator=(const raw_image_sdl& img);
public:
    raw_image_sdl();
    size_t width() const;
    size_t height() const;
    pixel_fmt_t fmt() const;
    void* data();

    raw_image_sdl(const std::string& img_file);
    bool load(const std::string& img_file);
    bool load(const std::string& text,
              const std::string& ttf_file,
              unsigned int fontsize = 16,
              const SDL_Color& color = {255,255,255});
    ~raw_image_sdl();
};
typedef raw_image_sdl raw_image;
typedef SDL_Color raw_color;
#endif




#endif
