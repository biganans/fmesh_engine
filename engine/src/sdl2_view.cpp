#include <sdl2_view.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <render/opengl/ogl.h>
#include <utils/log.h>
#include <input/input_manager.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

void sdl2_view::create_context(int width, int height, const std::string& name)
{
    screen_height = height;
    screen_width = width;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        sdldie("Unable to initialize SDL"); /* Or die on error */

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR);
    #ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    #endif
    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    mainwindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  screen_width, screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!mainwindow) {
        sdldie("Unable to create window");
    } else {
        windowed = true;
    }

    if (TTF_Init()==-1) {
        console::error("TTF_Init: %s\n", TTF_GetError());
        exit(-1);
    }

    maincontext = SDL_GL_CreateContext(mainwindow);
    init_glew();
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
}

void sdl2_view::quit()
{
    SDL_Quit();
}

void sdl2_view::sdldie(const char *msg)
{
    console::error("%s: %s", msg, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void sdl2_view::swap()
{
    SDL_GL_SwapWindow(mainwindow);
    SDL_Delay(10);
}

void sdl2_view::handle_events()
{
    // Our SDL event placeholder.
    SDL_Event event;
    //Grab all the events off the queue.
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            handle_key_event(&event.key.keysym);
            break;
        case SDL_QUIT:
            this->sdldie("die");
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                if (mainwindow) {
                    int tmpX,tmpY;
                    SDL_GetWindowSize(mainwindow, &tmpX, &tmpY);
                    //                    gl->resizeGL(tmpX, tmpY);
                }
            }
            SDL_GL_SwapWindow(mainwindow);
            break;
        }
    }
}
#include <game_object/camera.h>

static const float camera_move = 2.0f;
static float camera_off = 2.0f;
void sdl2_view::handle_key_event(SDL_Keysym* keysym)
{
    vec4 eye, center;
    quat r;

    switch (keysym->sym) {
    case SDLK_w:
        r = fmesh::camera::main_camera()->rotate();
        fmesh::camera::main_camera()->set_pos(fmesh::camera::main_camera()->pos() + r * vec3(0,0,camera_move));
        fmesh::camera::main_camera()->lookat();
        break;
    case SDLK_s:
        r = fmesh::camera::main_camera()->rotate();
        fmesh::camera::main_camera()->set_pos(fmesh::camera::main_camera()->pos() + r * vec3(0,0,-camera_move));
        fmesh::camera::main_camera()->lookat();
        break;
    case SDLK_a:
        r = fmesh::camera::main_camera()->rotate();
        fmesh::camera::main_camera()->set_pos(fmesh::camera::main_camera()->pos() + r * vec3(camera_move,0,0));
        fmesh::camera::main_camera()->lookat();
        break;
    case SDLK_d:
        r = fmesh::camera::main_camera()->rotate();
        fmesh::camera::main_camera()->set_pos(fmesh::camera::main_camera()->pos() + r * vec3(-camera_move,0,0));
        fmesh::camera::main_camera()->lookat();
        break;
    case SDLK_q:
        r = fmesh::camera::main_camera()->rotate()
            * glm::angleAxis((float)RADIAN(camera_off), vec3(0,1,0));
        fmesh::camera::main_camera()->set_rotate(r);
        fmesh::camera::main_camera()->lookat();
        break;
    case SDLK_e:
        r = fmesh::camera::main_camera()->rotate()
            * glm::angleAxis((float)RADIAN(-camera_off), vec3(0,1,0));
        fmesh::camera::main_camera()->set_rotate(r);
        fmesh::camera::main_camera()->lookat();
        break;
    case SDLK_ESCAPE:
        exit(EXIT_SUCCESS);
        break;
    case SDLK_SPACE:
        fmesh::g_input_manager::ref().add(0);
        break;
    case SDLK_F1:
        this->toggle_full_screen();
        break;
    case SDLK_r:
        fmesh::g_input_manager::ref().add(1);
        break;

    default:
        break;
    }
}

void sdl2_view::toggle_full_screen()
{
    if (windowed) {
        int result = SDL_SetWindowFullscreen(mainwindow, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN );
        //If there's an error
        if (result < 0) {
            windowOK = false;
            return;
        }
        windowed = false;
    } else {
        SDL_SetWindowSize(mainwindow, screen_width, screen_height);
        windowed = true;
    }
}

void sdl2_view::check_sdl_error(int line)
{
#if defined(DEBUG) || defined(_DEBUG)
    const char *error = SDL_GetError();
    if (error != NULL) {
        console::error("SDL %s", error);
        if (line != -1)
            console::log(" + line: %d\n", line);
        SDL_ClearError();
    }
#endif
}
