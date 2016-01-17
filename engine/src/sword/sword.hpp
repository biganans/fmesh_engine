#ifndef _SWORD_HPP_
#define _SWORD_HPP_

#include <game_object/game_object.h>
#include <game_object/transform3d.h>
#include <game_object/camera.h>
#include <utils/log.h>
#include <input/input_manager.h>

class sword : public fmesh::game_object
{
    enum {
        stand,
        swipe,
        swipe_end,
        fly,
    } state = stand;

    double _swipe_1 = 0.3;
    double _swipe_2 = 0.5;

    fmesh::transform3d _swipe_end;
    fmesh::transform3d _stand;

    double _time = 0;
public:
    virtual void update(double dt);
    void set_stand(const fmesh::transform3d& tf);
};


void sword::set_stand(const fmesh::transform3d& tf)
{
    this->_stand = tf;
    this->_swipe_end.pos = vec3(this->_stand.pos.x,
                                this->_stand.pos.y - 10.0f,
                                this->_stand.pos.z);
    this->_swipe_end.rotate = this->_stand.rotate * glm::angleAxis((float)RADIAN(180),
                                                                   vec3(0,0,1));
}


void sword::update(double dt)
{
    return;
    fmesh::transform3d *tf = this->get_component<fmesh::transform3d>();

    if (this->state == sword::swipe) {
        this->_time += dt;
        if (this->_time <= this->_swipe_1) {
            float f =  (float)(this->_time/this->_swipe_1);

            tf->pos = glm::mix(this->_stand.pos,
                               this->_swipe_end.pos,
                               f);

            tf->rotate = glm::mix(this->_stand.rotate,
                                  this->_swipe_end.rotate,
                                  f);
        } else {
            this->_time = 0;
            tf->pos = this->_swipe_end.pos;
            tf->rotate = this->_swipe_end.rotate;
            this->state = sword::swipe_end;
        }
        return;
    }

    if (this->state == sword::swipe_end) {
        this->_time += dt;
        if (this->_time <= this->_swipe_2) {
            float f =  (float)(this->_time/this->_swipe_2);

            tf->pos = glm::mix(this->_swipe_end.pos,
                               this->_stand.pos,
                               f);

            tf->rotate = glm::mix(this->_swipe_end.rotate,
                                  this->_stand.rotate,
                                  f);
        } else {
            this->_time = 0;
            *tf = this->_stand;
            this->state = sword::stand;
        }
        return;
    }


    if (!fmesh::g_input_manager::ref().empty()) {
        int key = fmesh::g_input_manager::ref().get_back();
        if (this->state == sword::stand) {
            this->state = sword::swipe;
            this->_time = 0;
        }

        fmesh::g_input_manager::ref().clear();
    }
}


#endif
