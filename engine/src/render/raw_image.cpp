#include <render/raw_image.h>
#include <cstring>
#include <iostream>
#include <cassert>

size_t raw_image_sdl::width() const
{
    assert(this->_surface);
    return this->_surface->w;
}

size_t raw_image_sdl::height() const
{
    assert(this->_surface);
    return this->_surface->h;
}

pixel_fmt_t raw_image_sdl::fmt() const
{
    assert(this->_surface);
    return this->_type;
}

void* raw_image_sdl::data()
{
    assert(this->_surface);
    return this->_surface->pixels;
}

void raw_image_sdl::pixel_format()
{
    SDL_PixelFormat *format = this->_surface->format;
    Uint32 fmt = format->format;
    switch (fmt) {
    case SDL_PIXELFORMAT_RGBA8888:
        this->_type = KTEX2D_RGBA8888;
        break;
    case SDL_PIXELFORMAT_RGBA4444:
        this->_type = KTEX2D_RGBA4444;
        break;
    case SDL_PIXELFORMAT_RGBA5551:
        this->_type = KTEX2D_RGBA5551;
        break;
    case SDL_PIXELFORMAT_RGB24:
        this->_type = KTEX2D_RGB888;
        break;
    case SDL_PIXELFORMAT_RGB888:
        this->_type = KTEX2D_RGB888;
        break;
    case SDL_PIXELFORMAT_BGR888:
        this->_type = KTEX2D_BGR888;
        break;
    case SDL_PIXELFORMAT_BGR24:
        this->_type = KTEX2D_BGR24;
        break;
    case SDL_PIXELFORMAT_RGB565:
        this->_type = KTEX2D_RGB565;
        break;
    default:
        this->_type = KTEX2D_RGBA8888;
        break;
    }
}


bool raw_image_sdl::load(const std::string& img_file)
{
    this->_surface = IMG_Load(img_file.c_str());
    if (this->_surface == NULL) {
        std::cerr << "ERROR: " << SDL_GetError() << std::endl;
        return false;
    }

    this->pixel_format();
    return true;
}


bool raw_image_sdl::load(const std::string& text,
                         const std::string& ttf_file,
                         unsigned int fontsize,
                         const SDL_Color& color)
{
    TTF_Font *font;
    font = TTF_OpenFontIndex(ttf_file.c_str(), fontsize * 20, 0);
    this->_surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    TTF_CloseFont(font);
    if (this->_surface == NULL) {
        std::cerr << "ERROR: " << SDL_GetError() << std::endl;
        return false;
    }
    this->_type = KTEX2D_RGBA8888;
    return true;
}


raw_image_sdl::raw_image_sdl()
{
}

raw_image_sdl::raw_image_sdl(const std::string& img_file)
{
    this->load(img_file);
}

raw_image_sdl::~raw_image_sdl()
{
    if (this->_surface != NULL) {
        SDL_FreeSurface(this->_surface);
    }
}
