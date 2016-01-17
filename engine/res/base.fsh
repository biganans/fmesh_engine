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

flat in int _is_rect;

uniform sampler2D tex2d_0;
uniform sampler2D normal_map;
uniform sampler2D gs_map;
uniform sampler2D rivers_map;
uniform sampler2D terrain_map;
uniform sampler2D atlas_map;
uniform sampler2D atlas_normal_map;
uniform sampler2D noise2d_map;


vec4 fetch_terrain(float x, float y, inout vec3 normal)
{
    float scale = 100.0f;
    mat3 t = mat3(0.25,  0,      0,
                  0,     0.25,   0,
                  x,     y,      1);

    vec2 t_uv = fract(uv * scale);
    vec2 new_uv = (t * vec3(t_uv.x, t_uv.y, 1.0)).xy;
    normal = unpack_normal(atlas_normal_map, uv_flip(new_uv)).xyz;
    return texture(atlas_map, uv_flip(new_uv));
}

vec4 terrain_color(inout vec3 normal)
{
    vec3 terrain = texture(terrain_map, uv_flip(uv)).rgb;

    const vec3 clear = vec3(86.0/255.0, 124.0/255.0, 27.0/255.0);
    const vec3 snow = vec3(1.0, 1.0, 1.0);
    const vec3 mountian = vec3(155.0/255.0, 155.0/255.0, 155.0/255.0);
    const vec3 fill = vec3(66.0/255.0, 42.0/255.0, 19.0/255.0);
    const vec3 woods = vec3(0, 86.0/255.0, 18.0f/255.0);
    vec4 ocolor;

    if (distance(terrain, clear) <= 0.1) {
        ocolor = fetch_terrain(0, 0.75, normal);
    } else if (distance(terrain,  snow) <= 0.1) {
        ocolor = fetch_terrain(0.75, 0.25, normal);
    } else if (distance(terrain, mountian) <= 0.1) {
        ocolor = fetch_terrain(0.5, 0.25, normal);
    } else if (distance(terrain, fill) <= 0.1) {
        ocolor = fetch_terrain(0.25, 0.25, normal);
    } else if (distance(terrain, woods) <= 0.1) {
        ocolor = fetch_terrain(0, 0.25, normal);
    } else  {
        ocolor = vec4(0.0);
        normal = vec3(0.0);
    }

    return ocolor;
}


void main()
{
    vec4 color;
    if (_is_rect == 1) {
        directional_light dl;
        dl.color = vec3(1.0f);
        dl.direction = vec3(0,1,0);
        dl.ambient_intensity = 1.0;
        dl.diffuse_intensity = 0.8;
        dl.specular_intensity = 0.8;
        dl.specular_power = 32;


        mat3 tbn = tbn_mat(normalize(es_tangent),
                           normalize(es_bitangent),
                           normalize(es_normal));

        vec4 rivers_color = texture(rivers_map, uv_flip(uv));
        vec4 gs_color = texture(gs_map, uv_flip(uv));


        vec4 ocolor = texture(tex2d_0, uv_flip(uv));
//        vec4 map_color = vec4(mix(rivers_color.rgb, ocolor.rgb, rivers_color.r), 1.0);
        vec4 map_color = ocolor;
        vec3 ts_tnormal = vec3(0.0);
        vec4 tcolor = terrain_color(ts_tnormal);
        tcolor = tcolor * calc_directional_light(dl,
                                                 (tbn * ts_tnormal),
                                                 es_vertex,
                                                 vec3(0,0,1));


        vec3 ts_normal = unpack_normal(normal_map, uv_flip(uv)).xyz;
        vec3 new_es_normal = tbn * ts_normal;
        vec4 light_color = calc_directional_light(dl,
                                                  new_es_normal,
                                                  es_vertex,
                                                  vec3(0,0,1));
        map_color = map_color * light_color;
        color = vec4(mix(map_color.rgb, tcolor.rgb, gs_color.rgb), 1.0);

    } else {
        directional_light dl;
        dl.color = vec3(1.0f);
        dl.direction = vec3(1,0,0);
        dl.ambient_intensity = 0.8;
        dl.diffuse_intensity = 0.6;
        dl.specular_intensity = 1.0f;
        dl.specular_power = 32;

        vec4 light_color = calc_directional_light(dl,
                                                  normalize(es_normal),
                                                  normalize(es_vertex),
                                                  vec3(0,0,1));
        color = vec4(0.8, 0.8, 0.3, 1.0) * light_color;
    }

    put_frag_color0(color);
}


