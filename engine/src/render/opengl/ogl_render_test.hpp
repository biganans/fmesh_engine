#ifndef _OGL_RENDER_TEST_HPP_
#define _OGL_RENDER_TEST_HPP_


static const float rectangle[] = {
    0.5, -0.5, 0,
    0.5, 0.5, 0,
    -0.5, -0.5, 0,
    -0.5, 0.5, 0};

static const char rindexs[] = {
    0,1,2,3
};


static ogl_buffer_object *g_vbo;
static ogl_buffer_object *g_ibo;

static texture *tex2d;
static texture *normal_map;
static texture *gs_map;
static texture *rivers_map;
static texture *terrain_map;
static texture *atlas_map;
static texture *atlas_normal_map;
static texture *noise2d_map;
static GLuint g_vao;

static ogl_program *g_program;
static inline void init_shader_test()
{
    ogl_preprocess pp;
    pp.exec(get_base_path() + "res/base.vsh");

    ogl_preprocess pf;
    pf.exec(get_base_path() + "res/base.fsh");

    g_program = new ogl_program();

    g_program->add_shader(pp.sources(), GL_VERTEX_SHADER);
    g_program->add_shader(pf.sources(), GL_FRAGMENT_SHADER);
    g_program->attach_link();
}

ogl_program* load_program(const std::string& vsh, const std::string& fsh)
{
    ogl_preprocess pp;
    pp.exec(vsh);

    ogl_preprocess pf;
    pf.exec(fsh);

    ogl_program *pg = new ogl_program();

    pg->add_shader(pp.sources(), GL_VERTEX_SHADER);
    pg->add_shader(pf.sources(), GL_FRAGMENT_SHADER);
    pg->attach_link();
    return pg;
}

material load_material(const std::string& diffuse, const std::string& specular, const std::string& normal)
{
    material m;
    m.diffuse_map = new ogl_texture();
    m.diffuse_map->load_tex2d(diffuse);

    m.specular_map = new ogl_texture();
    m.specular_map->load_tex2d(specular);

    m.normals_map = new ogl_texture();
    m.normals_map->load_tex2d(normal);
    return m;
}

void send(ogl_program* program, const material& m)
{
    glActiveTexture(GL_TEXTURE0);
    m.diffuse_map->bind();
    program->uniform1i("diffuse_color_map", 0);

    glActiveTexture(GL_TEXTURE0 + 1);
    m.specular_map->bind();
    program->uniform1i("specular_color_map", 1);

    glActiveTexture(GL_TEXTURE0 + 2);
    m.normals_map->bind();
    program->uniform1i("normal_map", 2);
}
static vec3 g_light;
static ogl_program *terrain_program;
static GLuint terrain_vao;
static texture *terrain_color_map;

static ogl_program *sword_program;
static mesh *sword;
static material sword_material;
static GLuint sword_vao;

static mesh *drone;
static material drone_material;
static GLuint drone_vao;


static mesh *mk23s;
static material mk23_material;
static GLuint mk23_vao;


static GLuint g_fbo;
static GLuint depath_texture;

static ogl_program *da_art_program;
static mesh *da_art;
static inline bool init_fboshadow_test()
{
    GLuint FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

    GLuint depthTexture;
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

    glDrawBuffer(GL_NONE); // No color buffer is drawn to.
    glReadBuffer(GL_NONE);

    // Always check that our framebuffer is ok
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return false;
    depath_texture = depthTexture;
    g_fbo = FramebufferName;
    return true;
}
extern int g_hit_count;
extern bool g_up_hit;
static inline void update_label_text()
{
    if (terrain_color_map) {
        delete terrain_color_map;
        terrain_color_map = NULL;
    }
    terrain_color_map = new ogl_texture();
    raw_image text;
    text.load("+" + to_string(g_hit_count), get_base_path() + "res/font/Symbol.ttf");
    terrain_color_map->load_image2d(text);
}

static inline void init_sword_test()
{
    g_light = vec3(0.0f, -1.0f, 0.0f);
    init_fboshadow_test();
    terrain_program   = load_program(get_base_path() + "res/terrain.vsh", get_base_path() + "res/terrain.fsh");
    terrain_vao       = get_vao();

    update_label_text();

    noise2d_map = new ogl_texture();
    noise2d_map->load_tex2d(get_base_path() + "res/noise_2d.jpg");


    sword_program = load_program(get_base_path() + "res/sword.vsh", get_base_path() + "res/sword.fsh");

    sword = new mesh();
    sword->load(get_base_path() + "res/sword/Wonder_Woman_Sword.dae");
    sword_material = load_material(get_base_path() + "/res/sword/Wonder_Woman_sword_D.tga",
                                   get_base_path() + "/res/sword/Wonder_Woman_sword_S.tga",
                                   get_base_path() + "/res/sword/Wonder_Woman_sword_N.tga");
    sword_vao = get_vao();

    drone = new mesh();
    drone->load(get_base_path() + "res/Drone/Drone.dae");
    drone_material = load_material(get_base_path() + "/res/Drone/Drone_D.tga",
                                   get_base_path() + "/res/Drone/Drone_S.tga",
                                   get_base_path() + "/res/Drone/Drone_N.tga");

    drone_vao = get_vao();


    mk23s = new mesh();
    mk23s->load(get_base_path() + "res/mk23/MK23.dae");
    mk23_material = load_material(get_base_path() + "/res/mk23/MK23_D.tga",
                                   get_base_path() + "/res/mk23/MK23_S.tga",
                                   get_base_path() + "/res/mk23/MK23_N.tga");

    da_art_program = load_program(get_base_path() + "res/base_obj.vsh", get_base_path() + "res/base_obj.fsh");
    da_art = new mesh();
    da_art->load(get_base_path() + "res/Tower/Tower.fbx");

    mk23_vao = get_vao();

    fmesh::camera::main_camera()->lookat();
}

static inline void draw_3dmodel_shadow(ogl_program *program,
                                       GLuint svao,
                                       const mesh::mesh_entry& entry)
{
    program->bind();

    float w = g_screen::ref().width;
    float h = g_screen::ref().height;

    glm::mat4 proj  = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
    glm::mat4 view  = glm::lookAt(g_light, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0);

    program->uniform_matrix4fv("projection", 1, 0, value_ptr(proj));
    program->uniform_matrix4fv("view", 1, 0, value_ptr(view));
    program->uniform_matrix4fv("model", 1, 0, value_ptr(model));
    glBindVertexArray(svao);
    entry.vbo->bind();
    entry.ibo->bind();

    program->enable_attr("pos");
    glVertexAttribPointer(program->get_attr("pos"), 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
    draw_elements_instanced(GL_TRIANGLES,
                            entry.numindices,
                            GL_UNSIGNED_INT,
                            0,
                            1);

    program->disable_attr("pos");
    glBindVertexArray(0);
}


static inline void draw_3dmodel(ogl_program *program,
                                GLuint svao,
                                const mesh::mesh_entry& entry,
                                const material& m,
                                const mat4& model)
{
    program->bind();

    send(program, m);

    float w = g_screen::ref().width;
    float h = g_screen::ref().height;
    program->uniform3f("g_light", g_light.x, g_light.y, g_light.z);

    mat4 proj = glm::perspective(45.0f, w / h, 0.1f, 1000.0f);
    //    mat4 proj = ortho(-w/2.0f, w/2.0f, -h/2.0f, h/2.0f, -1.0f, 1.0f);

    program->uniform_matrix4fv("projection", 1, 0, value_ptr(proj));

    const mat4& view = fmesh::camera::main_camera()->view();
    program->uniform_matrix4fv("view", 1, 0, value_ptr(view));
    program->uniform_matrix4fv("model", 1, 0, value_ptr(model));
    glBindVertexArray(svao);
    entry.vbo->bind();
    entry.ibo->bind();

    program->enable_attr("pos");
    program->enable_attr("normal");
    program->enable_attr("uv");
    program->enable_attr("tangent");

    glVertexAttribPointer(program->get_attr("pos"), 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
    glVertexAttribPointer(program->get_attr("normal"), 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertex), (GLvoid*)offsetof(vertex, normal));
    glVertexAttribPointer(program->get_attr("uv"), 2, GL_FLOAT, GL_FALSE,
                          sizeof(vertex), (GLvoid*)offsetof(vertex, uv));

    glVertexAttribPointer(program->get_attr("tangent"), 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertex), (GLvoid*)offsetof(vertex, tangent));

    draw_elements_instanced(GL_TRIANGLES,
                            entry.numindices,
                            GL_UNSIGNED_INT,
                            0,
                            1);

    program->disable_attr("pos");
    program->disable_attr("normal");
    program->disable_attr("uv");
    program->disable_attr("tangent");
    glBindVertexArray(0);
}

#include <game_object/transform3d.h>
#include <game_object/game_object.h>

static inline void draw_sword_shadow_test()
{
    glBindFramebuffer(GL_FRAMEBUFFER, g_fbo);

    fmesh::transform3d *drone_trans = fmesh::get_game_object(0)->get_component<fmesh::transform3d>();
    fmesh::transform3d *sword_trans = fmesh::get_game_object(1)->get_component<fmesh::transform3d>();

    mat4 drone_model = drone_trans->to_mat4();
    mat4 sword_model = sword_trans->to_mat4();

    draw_3dmodel_shadow(sword_program, drone_vao, drone->entries()[0]);
    draw_3dmodel_shadow(sword_program, sword_vao, sword->entries()[0]);

}

static inline void draw_sword_test()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    fmesh::transform3d *drone_trans = fmesh::get_game_object(0)->get_component<fmesh::transform3d>();
    fmesh::transform3d *sword_trans = fmesh::get_game_object(1)->get_component<fmesh::transform3d>();

    fmesh::transform3d *mk23_trans = fmesh::get_game_object(2)->get_component<fmesh::transform3d>();

    if (g_up_hit) {
        update_label_text();
        g_up_hit = false;
    }

    mat4 drone_model = drone_trans->to_mat4();
    mat4 sword_model = sword_trans->to_mat4();
    mat4 mk23_model = mk23_trans->to_mat4();

    draw_3dmodel(sword_program, drone_vao, drone->entries()[0], drone_material, drone_model);
    draw_3dmodel(sword_program, sword_vao, sword->entries()[0], sword_material, sword_model);

    draw_3dmodel(sword_program, mk23_vao, mk23s->entries()[0], mk23_material, mk23_model);
    mat4 city = glm::translate(vec3(-300.0f, 0.0f, 500.0f))  * glm::rotate((float)RADIAN(270), vec3(1, 0, 0)) *  glm::scale(vec3(0.1f, 0.1f, 0.1f));
    render_mesh(da_art_program, da_art, city, g_light);
}

static inline void draw_terrain_test()
{
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    terrain_program->bind();
    glBindVertexArray(terrain_vao);
    float w = g_screen::ref().width;
    float h = g_screen::ref().height;

    terrain_program->uniform3f("g_light", g_light.x, g_light.y, g_light.z);

    glActiveTexture(GL_TEXTURE0);
    terrain_color_map->bind();
    terrain_program->uniform1i("color_map", 0);

    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, depath_texture);
    terrain_program->uniform1i("shadow_map", 1);


    glActiveTexture(GL_TEXTURE0 + 2);
    noise2d_map->bind();
    terrain_program->uniform1i("noise2d_map", 2);

    mat4 proj = glm::perspective(45.0f, w / h, 0.1f, 1000.0f);
    terrain_program->uniform_matrix4fv("projection", 1, 0, value_ptr(proj));

    const mat4& view = fmesh::camera::main_camera()->view();
    terrain_program->uniform_matrix4fv("view", 1, 0, value_ptr(view));

    glm::mat4 biasMatrix(
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.5, 0.5, 0.5, 1.0
        );
    glm::mat4 sproj  = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
    glm::mat4 sview  = glm::lookAt(g_light, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 smodel = glm::mat4(1.0);
    glm::mat4 smvp   = biasMatrix * sproj * sview * smodel;
    terrain_program->uniform_matrix4fv("shadow_mvp", 1, 0, value_ptr(smvp));

    draw_arrays_instanced(GL_TRIANGLE_STRIP, 0, 4, 1);
    glDisable(GL_BLEND);
}


/*
static inline void init_monkey_test()
{
    g_vbo = new ogl_buffer_object(GL_ARRAY_BUFFER);
    g_vbo->data(sizeof(MeshVertexData), (void*)MeshVertexData);

    g_ibo = new ogl_buffer_object(GL_ELEMENT_ARRAY_BUFFER);
    g_ibo->data(sizeof(rindexs), (void*)rindexs);
}
*/

static inline void init_map_test()
{
    tex2d = new ogl_texture();
    tex2d->load_tex2d(get_base_path() + "/res/colormap.jpg");

    normal_map = new ogl_texture();
    normal_map->load_tex2d(get_base_path() + "/res/world_normal_height.jpg");

    gs_map = new ogl_texture();
    gs_map->load_tex2d(get_base_path() + "/res/gs_map.jpg");

    rivers_map = new ogl_texture();
    rivers_map->load_tex2d(get_base_path() + "/res/rivers.jpg");

    terrain_map = new ogl_texture();
    terrain_map->load_tex2d(get_base_path() + "/res/terrain.jpg");

    atlas_map = new ogl_texture();
    atlas_map->load_tex2d(get_base_path() + "/res/atlas.jpg");

    atlas_normal_map = new ogl_texture();
    atlas_normal_map->load_tex2d(get_base_path() + "/res/atlas_normal.jpg");

    noise2d_map = new ogl_texture();
    noise2d_map->load_tex2d(get_base_path() + "/res/noise_2d.jpg");

    glGenVertexArrays(1, &g_vao);
    fmesh::camera::main_camera()->lookat();
}

static inline void draw_map_test()
{
    g_program->bind();

//    this->polygon_mode(GL_LINE);
    float w = g_screen::ref().width;
    float h = g_screen::ref().height;;

    mat4 proj = glm::perspective(45.0f, w/h, 0.1f, 1000.0f);
//    mat4 proj = ortho(-w/2.0f, w/2.0f, -h/2.0f, h/2.0f, -1.0f, 1.0f);
    g_program->uniform_matrix4fv("projection", 1, 0, value_ptr(proj));

    const mat4& view = fmesh::camera::main_camera()->view();
    g_program->uniform_matrix4fv("view", 1, 0, value_ptr(view));

    glBindVertexArray(g_vao);
/*
    //---->start draw monkey
    g_vbo->bind();

    g_program->uniform1i(g_program->get_uniform("is_rect"), 0);
    g_program->enable_attr("pos");
    g_program->enable_attr("normal");

    glVertexAttribPointer(g_program->get_attr("pos"), 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
    glVertexAttribPointer(g_program->get_attr("normal"), 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, normal));

    draw_array_instanced(GL_TRIANGLES, 0, sizeof(MeshVertexData) / sizeof(vertex), 100);
    program->disable_attr("pos");
    program->disable_attr("normal");
    //---->end
*/
    //----start draw rect

    g_program->uniform1i("is_rect", 1);
    glActiveTexture(GL_TEXTURE0);
    tex2d->bind();
    g_program->uniform1i("tex2d_0", 0);

    glActiveTexture(GL_TEXTURE0 + 1);
    normal_map->bind();
    g_program->uniform1i("normal_map", 1);

    glActiveTexture(GL_TEXTURE0 + 2);
    gs_map->bind();
    g_program->uniform1i("gs_map", 2);

    glActiveTexture(GL_TEXTURE0 + 3);
    rivers_map->bind();
    g_program->uniform1i("rivers_map", 3);

    glActiveTexture(GL_TEXTURE0 + 4);
    terrain_map->bind();
    g_program->uniform1i("terrain_map", 4);

    glActiveTexture(GL_TEXTURE0 + 5);
    atlas_map->bind();
    g_program->uniform1i("atlas_map", 5);

    glActiveTexture(GL_TEXTURE0 + 6);
    atlas_normal_map->bind();
    g_program->uniform1i("atlas_normal_map", 6);

    glActiveTexture(GL_TEXTURE0 + 7);
    noise2d_map->bind();
    g_program->uniform1i("noise2d_map", 7);
    draw_arrays_instanced(GL_TRIANGLE_STRIP, 0, 4, 3);
    //----end
}


#endif
