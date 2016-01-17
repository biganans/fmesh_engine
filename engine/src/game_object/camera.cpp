#include <game_object/camera.h>

using namespace fmesh;


const mat4& camera::lookat()
{
    vec3 eye = (translate(this->_pos) * vec4(this->eye, 1.0)).xyz();
    vec3 center = (translate(this->_pos) * toMat4(this->_rotate) *  vec4(this->center, 1.0)).xyz();
    this->_view = lookAt(eye, center, this->up);
    return this->_view;
}

vec3 camera::get_eye() const
{
    return (translate(this->_pos) * vec4(this->eye, 1.0)).xyz();
}
