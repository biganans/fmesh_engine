#version 330
#include "geometry.gh"
#include "transfrom.gh"

layout(location = 0) in vec3 _pos;
layout(location = 1) in vec3 _normal;
layout(location = 2) in vec2 _uv;
layout(location = 3) in vec3 _tangent;

uniform mat4 _projection;
uniform mat4 _model;
uniform mat4 _view;

uniform vec3 _dlight;

out vec2 uv;
out vec3 es_normal;
out vec3 es_vertex;
out vec3 es_tangent;
out vec3 es_bitangent;
out vec3 es_dlight;

void main()
{
    vec4 vertex = vec4(_pos, 1.0);
    mat4 view_model = _view * _model;
    gl_Position = _projection * view_model * vertex;
    vec3 bitangent = cross(_normal, _tangent);
    es_normal = to_normal_mat(view_model) * _normal;
    es_tangent = to_normal_mat(view_model) * _tangent;
    es_bitangent = to_normal_mat(view_model) * bitangent;
    es_vertex = (view_model * vertex).xyz;
    es_dlight = mat3(_view) * _dlight;
    uv = _uv;
}
