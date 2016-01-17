#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <math/maths.h>
#include <game_object/component.h>
#include <utils/meta.h>

namespace fmesh {
class camera: public component
{
    vec3 eye    = vec3(0.0f, 0.0f ,0.0f);
    vec3 center = vec3(0.0f, 0.0f, 1.0f);
    vec3 up     = vec3(0.0f, 1.0f, 0.0f);

public:
    vec3 get_eye() const;
    $property(vec3, pos);
    $property(quat, rotate);
    $property_readonly(mat4, view);

    const mat4& lookat();
    $meta_type(camera, component_default_type::camera_type);

    static camera* main_camera()
    {
        static camera *__main_camera = NULL;
        if (__main_camera == NULL) {
            __main_camera = new camera();
            __main_camera->lookat();
        }
        return __main_camera;
    }
};
}



#endif
