#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <string>
#include <math/maths.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <render/opengl/ogl_buffer_object.h>
#include <render/opengl/ogl_vertex_array_object.h>

#include "texture.h"

struct vertex
{
    vec3 pos;
    vec3 normal;
    vec3 tangent;
    vec2 uv;
};

//TODO
struct material
{
    texture *diffuse_map = NULL;
    texture *specular_map = NULL;
    texture *normals_map = NULL;
};


class mesh
{
public:
    struct materials
    {
        std::string diffuse_map;
        std::string specular_map;
        std::string normals_map;
    };

#define INVALID_MATERIAL 0xFFFFFFFF
    struct mesh_entry
    {
        mesh_entry();
        ~mesh_entry();

        void init(const std::vector<vertex>& vertices,
                  const std::vector<unsigned int>& indices);

        ogl_buffer_object *vbo;
        ogl_buffer_object *ibo;
        ogl_vertex_array_object *vao;

        unsigned int material_index;
        unsigned int numindices;
    };

    mesh();
    ~mesh();

    bool load(const std::string& filename);

    const std::vector<mesh_entry>& entries() const;
    const std::vector<materials>& mtls() const;

private:
    bool init_from_scene(const aiScene* scene, const std::string& filename);
    void init_mesh(unsigned int index, const aiMesh* aimesh);
    bool init_materials(const aiScene* scene, const std::string& filename);
    void clear();

    std::vector<mesh_entry> _entries;
    std::vector<materials> _mtls;
};


#endif
