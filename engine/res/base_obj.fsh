#version 330
#include "phong.gh"
#include "render_pass.gh"
#include "geometry.gh"
#include "transfrom.gh"

in vec2 uv;
in vec3 es_normal;
in vec3 es_vertex;
in vec3 es_tangent;
in vec3 es_bitangent;
in vec3 es_dlight;

uniform sampler2D _diffuse_map;
uniform sampler2D _specular_map;
uniform sampler2D _normal_map;

void main()
{
    vec4 color;
    directional_light dl;
    dl.color = vec3(1.0f);
    dl.direction = normalize(es_dlight);
    dl.ambient_intensity = 0.2f;
    dl.diffuse_intensity = 0.3f;
    dl.specular_intensity = 0.0f;
    dl.specular_power = 0.0f;

    vec4 light_color = calc_directional_light(dl,
                                              es_normal,
                                              es_vertex,
                                              vec3(0,0,1));
    color = texture(_diffuse_map, uv).rgba * light_color;
    put_frag_color0(color);

}
