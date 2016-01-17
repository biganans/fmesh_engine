#version 330
#include "phong.gh"
#include "render_pass.gh"
#include "geometry.gh"
#include "transfrom.gh"

in vec2 out_uv;
in vec3 es_normal;
in vec3 es_vertex;
in vec3 es_tangent;
in vec3 es_bitangent;
in vec3 es_directional_light;

uniform sampler2D diffuse_color_map;
uniform sampler2D specular_color_map;
uniform sampler2D normal_map;

void main()
{
    vec4 color;
    directional_light dl;
    dl.color = vec3(1.0f);
    dl.direction = normalize(es_directional_light);
    dl.ambient_intensity = 1.0f;
    dl.diffuse_intensity = 1.0f;
    dl.specular_intensity = 0.8f;
    dl.specular_power = 32.0f;

    mat3 tbn = tbn_mat(normalize(es_tangent),
                       normalize(es_bitangent),
                       normalize(es_normal));

    vec3 ts_normal = unpack_normal(normal_map, out_uv).bgr;
    vec3 es_new_normal = tbn * ts_normal;

    vec4 light_color = calc_directional_light(dl,
                                              es_new_normal,
                                              es_vertex,
                                              vec3(0,0,1));
    color = texture(diffuse_color_map, out_uv).rgba * light_color;
    put_frag_color0(color);

}
