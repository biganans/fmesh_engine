#include <render/opengl/ogl_renderer.h>
#include <render/opengl/ogl_preprocess.h>
#include <render/opengl/ogl_texture.h>
#include <render/opengl/ogl_buffer_object.h>
#include <render/opengl/ogl_sysinfo.h>
#include <render/opengl/ogl_program.h>
#include <render/opengl/ogl_texture.h>
#include <render/opengl/ogl_func.h>
#include <render/mesh.h>
#include <render/texture_manager.h>
#include <game_object/camera.h>
#include <utils/log.h>
#include <utils/file.h>
#include <display/screen.h>


#define V_POS          "_pos"
#define V_NORMAL       "_normal"
#define V_UV           "_uv"
#define V_TANGENT      "_tangent"
#define U_DIFFUSE_MAP  "_diffuse_map"
#define U_SPECULAR_MAP "_specular_map"
#define U_NORMALS_MAP  "_normals_map"
#define U_PROJECTION   "_projection"
#define U_VIEW         "_view"
#define U_MODEL        "_model"
#define U_DLIGHT       "_dlight"

static inline GLuint get_vao()
{
    GLuint vaobj;
    glGenVertexArrays(1, &vaobj);
    glBindVertexArray(vaobj);
    return vaobj;
}

static void load_mtl(const mesh::materials& mtl)
{
    if (!mtl.diffuse_map.empty()) {
        g_texture_manager::ref().add_tex2d(mtl.diffuse_map);
    }

    if (!mtl.specular_map.empty()) {
        g_texture_manager::ref().add_tex2d(mtl.specular_map);
    }

    if (!mtl.normals_map.empty()) {
        g_texture_manager::ref().add_tex2d(mtl.normals_map);
    }
}

static void send_mtl(ogl_program *program, const mesh::materials& mtl)
{
    if (!mtl.diffuse_map.empty()) {
        texture *kd = g_texture_manager::ref().get(mtl.diffuse_map);
        if (kd) {
            glActiveTexture(GL_TEXTURE0);
            kd->bind();
            program->uniform1i(U_DIFFUSE_MAP, 0);
        }
    }

    if (!mtl.specular_map.empty()) {
        texture *sd = g_texture_manager::ref().get(mtl.specular_map);
        if (sd) {
            glActiveTexture(GL_TEXTURE0 + 1);
            sd->bind();
            program->uniform1i(U_SPECULAR_MAP, 1);
        }
    }

    if (!mtl.normals_map.empty()) {
        texture *nd = g_texture_manager::ref().get(mtl.normals_map);
        if (nd) {
            glActiveTexture(GL_TEXTURE0 + 2);
            nd->bind();
            program->uniform1i(U_NORMALS_MAP, 2);
        }
    }

}

static void render_mesh_entry(ogl_program *program,
                              const mesh::mesh_entry& entry,
                              const mesh::materials& m,
                              const mat4& model,
                              const vec3& dlight)
{
    program->bind();
    send_mtl(program, m);

    float w = g_screen::ref().width;
    float h = g_screen::ref().height;
    program->uniform3f(U_DLIGHT, dlight.x, dlight.y, dlight.z);
    mat4 proj = glm::perspective(45.0f, w / h, 0.1f, 1000.0f);
    //    mat4 proj = ortho(-w/2.0f, w/2.0f, -h/2.0f, h/2.0f, -1.0f, 1.0f);

    program->uniform_matrix4fv(U_PROJECTION, 1, 0, value_ptr(proj));
    const mat4& view = fmesh::camera::main_camera()->view();
    program->uniform_matrix4fv(U_VIEW, 1, 0, value_ptr(view));
    program->uniform_matrix4fv(U_MODEL, 1, 0, value_ptr(model));
    entry.vao->bind();
    entry.vbo->bind();
    entry.ibo->bind();

    program->enable_attr(V_POS);
    program->enable_attr(V_NORMAL);
    program->enable_attr(V_UV);
    program->enable_attr(V_TANGENT);

    glVertexAttribPointer(program->get_attr(V_POS), 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
    glVertexAttribPointer(program->get_attr(V_NORMAL), 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertex), (GLvoid*)offsetof(vertex, normal));
    glVertexAttribPointer(program->get_attr(V_UV), 2, GL_FLOAT, GL_FALSE,
                          sizeof(vertex), (GLvoid*)offsetof(vertex, uv));

    glVertexAttribPointer(program->get_attr(V_TANGENT), 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertex), (GLvoid*)offsetof(vertex, tangent));

    draw_elements_instanced(GL_TRIANGLES,
                            entry.numindices,
                            GL_UNSIGNED_INT,
                            0,
                            1);

    program->disable_attr(V_POS);
    program->disable_attr(V_NORMAL);
    program->disable_attr(V_UV);
    program->disable_attr(V_TANGENT);
    glBindVertexArray(0);
}


static void render_mesh(ogl_program *program,
                        const mesh *m,
                        const mat4& model,
                        const vec3& dlight)
{
    for (auto& entry : m->entries()) {
        load_mtl(m->mtls()[entry.material_index]);
        render_mesh_entry(program, entry, m->mtls()[entry.material_index], model, dlight);
    }
}

#include "ogl_render_test.hpp"


ogl_renderer::ogl_renderer()
{
//    init_shader_test();
//    init_map_test();
    init_sword_test();
}



void ogl_renderer::viewport(int x, int y, int w, int h)
{
    glViewport(x, y, w, h);
}

void ogl_renderer::clear_color(float r, float g, float b, float a)
{
    this->_color = vec4(r, g, b, a);
}

void ogl_renderer::clear()
{
    this->disable(render_enable_cap::scissor_test);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glStencilMask(0xFFFFFFFF);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}


void ogl_renderer::draw(double dt)
{
    this->viewport(0, 0, g_screen::ref().width, g_screen::ref().height);
    this->clear();
    this->enable(render_enable_cap::depth_test);
    this->enable(render_enable_cap::texture_2d);
    glClearColor(this->_color.r, this->_color.g, this->_color.b, this->_color.a);
//    draw_map_test();
    draw_sword_test();
    draw_terrain_test();
}

void ogl_renderer::enable(enum render_enable_cap cap)
{
    if (this->_enable_cache.find(cap) != this->_enable_cache.end()) {
        return;
    }

    switch (cap) {
    case render_enable_cap::texture_2d:
        glEnable(GL_TEXTURE_2D);
        break;
    case render_enable_cap::cull_face:
        glEnable(GL_CULL_FACE);
        break;
    case render_enable_cap::blend:
        glEnable(GL_BLEND);
        break;
    case render_enable_cap::dither:
        glEnable(GL_DITHER);
        break;
    case render_enable_cap::stencil_test:
        glEnable(GL_STENCIL_TEST);
        break;
    case render_enable_cap::depth_test:
        glEnable(GL_DEPTH_TEST);
        break;
    case render_enable_cap::scissor_test:
        glEnable(GL_SCISSOR_TEST);
        break;
    case render_enable_cap::polygon_offset_fill:
        glEnable(GL_POLYGON_OFFSET_FILL);
        break;
    case render_enable_cap::sample_alpha_to_coverage:
        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        break;
    case render_enable_cap::sample_coverage:
        glEnable(GL_SAMPLE_COVERAGE);
        break;
    }
    this->_enable_cache.insert(cap);
}


void ogl_renderer::disable(enum render_enable_cap cap)
{
    if (this->_enable_cache.find(cap) == this->_enable_cache.end()) {
        return;
    }

    switch (cap) {
    case render_enable_cap::texture_2d:
        glDisable(GL_TEXTURE_2D);
        break;
    case render_enable_cap::cull_face:
        glDisable(GL_CULL_FACE);
        break;
    case render_enable_cap::blend:
        glDisable(GL_BLEND);
        break;
    case render_enable_cap::dither:
        glDisable(GL_DITHER);
        break;
    case render_enable_cap::stencil_test:
        glDisable(GL_STENCIL_TEST);
        break;
    case render_enable_cap::depth_test:
        glDisable(GL_DEPTH_TEST);
        break;
    case render_enable_cap::scissor_test:
        glDisable(GL_SCISSOR_TEST);
        break;
    case render_enable_cap::polygon_offset_fill:
        glDisable(GL_POLYGON_OFFSET_FILL);
        break;
    case render_enable_cap::sample_alpha_to_coverage:
        glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        break;
    case render_enable_cap::sample_coverage:
        glDisable(GL_SAMPLE_COVERAGE);
        break;
    }

    this->_enable_cache.erase(cap);
}



void ogl_renderer::polygon_mode(GLenum mode)
{
#if GL_SYS_TYPE == GL_PROFILE_TYPE
    if (mode != this->_polygon_mode) {
        // opengl3.2+ only support GL_FRONT_AND_BACK
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //line mode
        glPolygonMode(GL_FRONT_AND_BACK, mode);
        this->_polygon_mode = mode;
    }
#endif
}


enum renderer::type ogl_renderer::type() const
{
    return renderer::type::GL;
}
