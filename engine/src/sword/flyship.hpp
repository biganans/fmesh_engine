#ifndef _FLYSHIP_HPP_
#define _FLYSHIP_HPP_

#include <game_object/game_object.h>
#include <game_object/transform3d.h>
#include <game_object/camera.h>

class flyship : public fmesh::game_object
{
    int state = 0;
public:
    void update(double dt);
};


void flyship::update(double dt)
{
    int speed = 100*dt;
    int edge = 200;
    fmesh::transform3d *trans = this->get_component<fmesh::transform3d>();
    if (state == 0) {
        trans->pos.x = trans->pos.x + speed;
        state = 1;
    } else if (state == 1) {
        if (trans->pos.x >= edge) {
            state = 2;
        } else {
            trans->pos.x = trans->pos.x + speed;
        }
    } else if (state == 2) {
        if (trans->pos.x <= -edge) {
            state = 1;
        } else {
            trans->pos.x = trans->pos.x - speed;
        }
    }

//    console::log("%lf", dt);
}


#endif
