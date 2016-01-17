#version 330
#include "geometry.gh"
#include "transfrom.gh"

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;

uniform int is_rect;

out vec2 uv;
out vec3 es_normal;
out vec3 es_vertex;
out vec3 es_tangent;
out vec3 es_bitangent;


flat out int _is_rect;

void main()
{
    const vec3 rectangle[4] = vec3[4](
        vec3(0.5, -0.5, 0.0),
        vec3(0.5, 0.5, 0.0),
        vec3(-0.5, -0.5, 0.0),
        vec3(-0.5, 0.5, 0.0));

    const vec2 rectuv[4] = vec2[4](
        vec2(1.0, 0.0),
        vec2(1.0, 1.0),
        vec2(0.0, 0.0),
        vec2(0.0, 1.0));

    float h = 5.8f * 2.0f;
    float w = 5.8f * 2.0f;

    mat4 model;
    vec4 vertex;
    vec3 _normal;

    vec3 _tangent_os;
    vec3 _bitangent_os;


    if (is_rect == 1) {
        if (gl_InstanceID == 0) {
            model = translate(0, 0, 20.0f) * scale(w, h, 1.0);
            uv = rectuv[gl_VertexID];
        } else if (gl_InstanceID == 1) {
            mat4 r = rotate(0,1,0, radians(90.0));
            model = translate(5.8f, 0, 0) * r * scale(1000.0f, h, 1.0f);
            uv = (scale(1000.0/w, 1, 1) * vec4(rectuv[gl_VertexID], 0, 1)).st;
        } else if (gl_InstanceID == 2) {
            model = translate(-5.8f, 0, 0) * rotate(0,1,0, radians(-90.0)) * scale(1000.0f, h, 1.0f);
            uv = (scale(1000.0/w, 1, 1) * vec4(rectuv[gl_VertexID], 0, 1)).st;
        }
        vertex = vec4(rectangle[gl_VertexID], 1.0);
        _normal = calc_triangle_normal(rectangle[0], rectangle[1], rectangle[2]);

        _tangent_os = calc_tangent(rectangle[0], rectangle[1], rectangle[2],
                                   rectuv[0], rectuv[1], rectuv[2]);

        _bitangent_os = cross(_normal, _tangent_os);

    } else {
        int x = gl_InstanceID % 10;
        int y = gl_InstanceID / 10;
        model = translate(100.0f * x, 0, 100.0f * y) * rotate(0,1,0, radians(180.0)) * scale(50,50,50);
        vertex = vec4(pos, 1.0);
        _normal = normal;
    }

    mat4 model_view = view * model;
    gl_Position = projection * model_view * vertex;

    es_normal = to_normal_mat(model_view) * _normal;
    es_vertex = (model_view * vertex).xyz;

    if (is_rect == 1) {
        es_tangent = to_normal_mat(model_view) * _tangent_os;
        es_bitangent = to_normal_mat(model_view) * _bitangent_os;
    }

    _is_rect = is_rect;
}
