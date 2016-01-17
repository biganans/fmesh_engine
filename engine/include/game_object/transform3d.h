#ifndef _TRANSFORM3D_H_
#define _TRANSFORM3D_H_
#include <math/maths.h>
#include <game_object/component.h>
#include <utils/meta.h>

namespace fmesh {
class transform3d: public component {
public:
    vec3 pos;
    vec3 scale;
    quat rotate;

    mat4 to_mat4() const
    {
        return translate(this->pos) * toMat4(this->rotate) * glm::scale(this->scale);
    }

    operator mat4() const
    {
        return this->to_mat4();
    }

    $meta_type(transform3d, component_default_type::transform3d_type);
};


}
#endif
