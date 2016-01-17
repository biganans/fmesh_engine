#include <application.h>
#include <chrono>
#include <render/renderer.h>
#include <game_object/game_object.h>
#include <display/screen.h>
#include <sdl2_view.h>
#include <cstring>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <input/input_manager.h>
#include <utils/bytestream.h>

#if defined(USE_GFX)
#include <GFx.h>
#endif

struct hand_pack
{
    int32_t x;
    int32_t y;
    char type;
};

std::deque<hand_pack> g_hand_manager;

#include <socket/Socket.hpp>
//@TEST
#include "sword/sword.hpp"
#include "sword/flyship.hpp"
#include "sword/mk23.hpp"

#define HAND_PACK_LEN (sizeof(char) + (sizeof(int32_t) * 2))

static int g_tcp_port = 56789;
static std::vector<hand_pack> g_commands;
static std::mutex g_packs_mutex;
static void client_handle(Socket::TCP client)
{
    char head[4] = {0};
    char buf[1024] = {0};
//    std::chrono::milliseconds dura(2000);
//    std::this_thread::sleep_for(dura);
    std::cout << client.ip() << " client open" << std::endl;
    while (1) {
        try {
            memset(head, 0, sizeof(head));
            int l = client.recv(head, sizeof(head));
            if (l < 4) goto quit;

            uint32_t len = *((uint32_t*)head); //@TODO char order
            if (len <= 0) goto quit;

            client.recv(buf, len);
            std::lock_guard<std::mutex> lk(g_packs_mutex);
            for (int i = 0; i < len; i += HAND_PACK_LEN) {
                hand_pack p;
                p.type = *(buf + i);
                p.x = *((int32_t*)(buf + i + sizeof(char)));
                p.y = *((int32_t*)(buf + i + sizeof(char) + sizeof(int32_t)));
                g_commands.push_back(p);
            }
        } catch (Socket::SocketException &e) {
            std::cout << e << std::endl;
            goto quit;
        }
    }
quit:
    std::cout << client.ip() << " client close" << std::endl;
    client.close();
}

static void start_tcp_server(int port)
{
    Socket::TCP server;
    try {
        server.listen_on_port(port);
        while (1) {
            Socket::TCP client = server.accept();
            std::thread client_thrd(client_handle, client);
            client_thrd.detach();
        }
    } catch (Socket::SocketException &e) {
        std::cout << e << std::endl;
        server.close();
        return;
    }
}

static void send_command()
{
    std::lock_guard<std::mutex> lk(g_packs_mutex);
    for (auto c : g_commands) {
        if (c.type == 0) {
            fmesh::g_input_manager::ref().add(0);
        } else {
            g_hand_manager.push_back(c);
        }
    }
    g_commands.clear();
}


application::application(int argc, const char **argv)
{
    g_screen::ref().width = 1024;
    g_screen::ref().height = 768;


    flyship *ship = new flyship();
    fmesh::transform3d *ship_tf = new fmesh::transform3d();
    ship_tf->scale = vec3(20.0f, 20.0f, 20.0f);
    ship_tf->pos = vec3(0, -10.0f, 150.0f);
    ship_tf->rotate = glm::angleAxis((float)RADIAN(180.0f), vec3(0, 1, 0)) * glm::angleAxis((float)RADIAN(270.0f), vec3(1, 0, 0));
    ship->add_component(ship_tf);

    sword *s = new sword();
    fmesh::transform3d *s_tf = new fmesh::transform3d();
    s_tf->scale = vec3(10.0f, 10.0f, 10.0f);
    s_tf->pos = vec3(-8.0f, -5.0f, 15.0f);
    s_tf->rotate = glm::angleAxis((float)RADIAN(180.0f), vec3(1, 0, 0)) *
        glm::angleAxis((float)RADIAN(30.0f), vec3(0, 0, 1)) *
        glm::angleAxis((float)RADIAN(60.0f), vec3(0, 1, 0));

    s->add_component(s_tf);
    s->set_stand(*s_tf);

    mk23 *m = new mk23();
    fmesh::transform3d *mk23_tf = new fmesh::transform3d();
    mk23_tf->scale = vec3(10.0f, 10.0f, 10.0f);
    mk23_tf->pos = vec3(6.0f, -3.0f, 11.0f);

    mk23_tf->rotate = glm::angleAxis((float)RADIAN(-90.0f), vec3(1, 0, 0));

    m->add_component(mk23_tf);
    m->set_stand(*mk23_tf);

    std::thread tcp_thrd(start_tcp_server, g_tcp_port);
    std::cout << "listen: " << g_tcp_port << std::endl;
    tcp_thrd.detach();
}

application::~application()
{
}

int application::run()
{
    sdl2_view *view;
    int w = g_screen::ref().width;
    int h = g_screen::ref().height;
    enum renderer::type rtype = renderer::type::GL;
    if (rtype == renderer::type::GL) {
        view = new sdl2_view();
        view->create_context(w, h, "Death Gun Display Server");
    } else {
        console::error("no backend");
        exit(-1);
    }

    g_renderer = renderer::alloc(rtype);
    std::chrono::time_point<std::chrono::high_resolution_clock>  start, end;
    std::chrono::duration<double> elapsed_seconds;
    double frametime = 0;
    while (1) {
        start = std::chrono::high_resolution_clock::now();
        g_renderer->clear_color(0, 0, 0, 1.0);
        send_command();

        fmesh::pre_update_all();
        fmesh::update_all(frametime);
        g_renderer->draw(frametime);
        view->handle_events();
        view->swap();
        fmesh::final_update_all();
        end = std::chrono::high_resolution_clock::now();
        elapsed_seconds = end - start;
        frametime = elapsed_seconds.count();
    }

    delete g_renderer;

    view->quit();
    delete view;
    return 0;
}
