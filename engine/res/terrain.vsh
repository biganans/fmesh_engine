#version 330
#include "geometry.gh"
#include "transfrom.gh"

uniform mat4 projection;
uniform mat4 view;

uniform mat4 shadow_mvp;
uniform vec3 g_light;
out vec3 es_normal;
out vec3 es_vertex;
out vec3 es_directional_light;
out vec2 out_uv;
out vec4 out_shadow_uv;


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

    mat4 model = translate(0.0f,45.0f,100.0f) * rotate(0,0,1, radians(180.0f)) * scale(20, 20, 1.0);

    vec4 vertex = vec4(rectangle[gl_VertexID], 1.0);

    vec3 _normal = calc_triangle_normal(rectangle[0], rectangle[1], rectangle[2]);
    mat4 model_view = view * model;
    gl_Position = projection * model_view * vertex;


    out_uv = (scale(1, 1, 1) * vec4(rectuv[gl_VertexID], 0, 1)).st;

    es_normal = to_normal_mat(model_view) * _normal;
    es_vertex = (model_view * vertex).xyz;
    es_directional_light = mat3(view) * g_light;
    out_shadow_uv = shadow_mvp * vertex;
}
