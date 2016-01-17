#include <game_object/game_object.h>
#include <game_object/alloc_id.h>

using namespace fmesh;
using namespace std;

//TODO
std::unordered_map<uint64_t, game_object*> __game_object_manager;

static inline void add_game_object(game_object *obj)
{
    __game_object_manager.insert(std::make_pair(obj->uid(), obj));
}

static inline void erase_game_object(game_object *obj)
{
    if (__game_object_manager.find(obj->uid()) != __game_object_manager.end()) {
        __game_object_manager.erase(obj->uid());
    }
}

game_object* fmesh::get_game_object(uint64_t uid)
{
    if (__game_object_manager.find(uid) != __game_object_manager.end()) {
        return __game_object_manager[uid];
    }
    return NULL;
}

void fmesh::pre_update_all()
{
    for (auto obj : __game_object_manager) {
        obj.second->pre_update();
    }
}

void fmesh::update_all(double dt)
{
    for (auto obj : __game_object_manager) {
        obj.second->update(dt);
    }
}

void fmesh::final_update_all()
{
    for (auto obj : __game_object_manager) {
        obj.second->final_update();
    }
}


game_object::game_object():_uid(alloc_game_object_id())
{
    add_game_object(this);
}


game_object::~game_object()
{
    erase_game_object(this);
}

void game_object::pre_update()
{
}

void game_object::update(double dt)
{
}

void game_object::final_update()
{
}

void game_object::add_component(component *cp)
{
    this->_components.insert(std::make_pair(cp->get_type(), cp));
}

component* game_object::get_component(int type)
{
    return this->_components[type];
}
