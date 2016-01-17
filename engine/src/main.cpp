#include <application.h>

#undef main //hack SDL_main bug
#if defined(_MSC_VER)
#pragma execution_character_set("UTF-8")
#endif

int main(int argc, const char** argv)
{
    application app(argc, argv);
    return app.run();
}
