#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <iostream>
#include <unordered_map>
#include <cstdint>
#include <utils/meta.h>

#include "component.h"

namespace fmesh {

class game_object
{
    std::unordered_map<int, component*> _components;
public:
    game_object();
    $property_readonly(uint64_t, uid);
    void add_component(component *cp);
    component* get_component(int type);

    template<typename T>
    T* get_component()
    {
        return static_cast<T*>(get_component(T::type()));
    }

    virtual void pre_update();
    virtual void update(double dt);
    virtual void final_update();

    virtual ~game_object();
};
extern game_object *get_game_object(uint64_t uid);
extern void pre_update_all();
extern void update_all(double dt);
extern void final_update_all();


}

#endif
