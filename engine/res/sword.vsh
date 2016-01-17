#version 330
#include "geometry.gh"
#include "transfrom.gh"

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 tangent;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

uniform vec3 g_light;
uniform int is_shadow;


out vec2 out_uv;
out vec3 es_normal;
out vec3 es_vertex;
out vec3 es_tangent;
out vec3 es_bitangent;
out vec3 es_directional_light;
void main()
{
    vec4 vertex = vec4(pos, 1.0);
    mat4 view_model = view * model;
    gl_Position = projection * view_model * vertex;
    vec3 bitangent = cross(normal, tangent);
    es_normal = to_normal_mat(view_model) * normal;
    es_tangent = to_normal_mat(view_model) * tangent;
    es_bitangent = to_normal_mat(view_model) * bitangent;
    es_vertex = (view_model * vertex).xyz;
    es_directional_light = mat3(view) * g_light;
    out_uv = uv;
}
