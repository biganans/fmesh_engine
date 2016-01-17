#version 330
#include "phong.gh"
#include "render_pass.gh"
#include "geometry.gh"
#include "transfrom.gh"

uniform sampler2D color_map;
uniform sampler2D shadow_map;
uniform sampler2D noise2d_map;

in vec3 es_normal;
in vec3 es_vertex;
in vec3 es_directional_light;
in vec2 out_uv;
in vec4 out_shadow_uv;

void main()
{
    vec4 color = texture(color_map, out_uv);
    put_frag_color0(color);

/*
    float visibility = 1.0;
    if (texture(shadow_map, out_shadow_uv.xy).z < out_shadow_uv.z){
        visibility = 0.5;
    }

    vec4 color;
    directional_light dl;
    dl.color = vec3(1.0f);
    dl.direction = normalize(es_directional_light);
    dl.ambient_intensity = 1.0f;
    dl.diffuse_intensity = 1.0f;
    dl.specular_intensity = 1.0f;
    dl.specular_power = 32.0f;

    vec3 noise = texture(noise2d_map, out_uv).xyz;

    vec4 light_color = calc_directional_light(dl,
                                              es_normal,
                                              es_vertex,
                                              vec3(0,0,1));

    color = texture(color_map, uv_flip(out_uv)) * light_color;
    put_frag_color0(color);
*/
}
