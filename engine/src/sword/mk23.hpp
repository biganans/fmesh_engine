#ifndef _MK23_HPP_
#define _MK23_HPP_


#include <game_object/game_object.h>
#include <game_object/transform3d.h>
#include <game_object/camera.h>
#include <utils/log.h>
#include <input/input_manager.h>

class mk23 : public fmesh::game_object
{
    enum {
        stand,
        aim_start,
        aim,
        aim_end,
        fire,
        fire_end
    } state = aim;

    double _time = 0;
    fmesh::transform3d _stand;
    fmesh::transform3d _aim_1_tf;
    fmesh::transform3d _fire_1_tf;
    double _aim_1 = 0.3;
    double _aim_2 = 0.5;

    double _fire_1 = 0.1;
    double _fire_2 = 0.15;
    int _hand_x = 0;

public:
    virtual void update(double dt);
    void set_stand(const fmesh::transform3d& tf);
    void dofire();
};


int g_hit_count = 0;
bool g_up_hit = false;
void mk23::dofire()
{
    fmesh::transform3d *tf = this->get_component<fmesh::transform3d>();
    float x = tf->pos.x;
    fmesh::transform3d *drone_trans = fmesh::get_game_object(0)->get_component<fmesh::transform3d>();
    float flyship_x = drone_trans->pos.x;
    float off = x - flyship_x;
    if (abs(off) < 40) {
        ++g_hit_count;
        g_up_hit = true;
        console::log("hit flyship"); //TODO
    }

}

void mk23::update(double dt)
{
    fmesh::transform3d *tf = this->get_component<fmesh::transform3d>();
    if (!g_hand_manager.empty()) {
        if (this->_hand_x == 0) {
            this->_hand_x = g_hand_manager.back().x;
        } else {
            if (this->state == mk23::aim) {
                int off = g_hand_manager.back().x - this->_hand_x;
                this->_hand_x = g_hand_manager.back().x;
                tf->pos.x = tf->pos.x + off * 0.1;
            }
        }
    }

    g_hand_manager.clear();
    if (this->state == mk23::fire) {
        this->_time += dt;
        if (this->_time <= this->_fire_1) {
            float f =  (float)(this->_time/this->_fire_1);
            tf->rotate = glm::mix(
                                  this->_stand.rotate,
                                  this->_fire_1_tf.rotate,
                                  f);
        } else {
            this->_time = 0;
            tf->rotate = this->_fire_1_tf.rotate;
            this->state = mk23::fire_end;
        }
        return;
    }

    if (this->state == mk23::fire_end) {
        this->_time += dt;
        if (this->_time <= this->_fire_2) {
            float f = (float)(this->_time/this->_fire_2);
            tf->rotate = glm::mix(this->_fire_1_tf.rotate,
                                  this->_stand.rotate,
                                  f);
        } else {
            this->_time = 0;
            tf->rotate = this->_stand.rotate;
            this->state = mk23::aim;
        }
        return;
    }

    if (!fmesh::g_input_manager::ref().empty()) {
        int key = fmesh::g_input_manager::ref().get_back();
        if (key == 0) {
            if (this->state == mk23::aim) {
                this->dofire();
                this->state = mk23::fire;
                this->_time = 0;
            }
        }
    }

}

void mk23::set_stand(const fmesh::transform3d& tf)
{
    this->_stand = tf;
    this->_fire_1_tf.rotate = tf.rotate *
        glm::angleAxis((float)RADIAN(-30),
                       vec3(1,0,0));
}


#endif
