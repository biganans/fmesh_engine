#include <render/mesh.h>
#include <utils/log.h>
#include <utils/str.h>

mesh::mesh_entry::mesh_entry():vbo(NULL), ibo(NULL), vao(NULL)
{

}

mesh::mesh_entry::~mesh_entry()
{
}

void mesh::mesh_entry::init(const std::vector<vertex>& vertices,
                            const std::vector<unsigned int>& indices)
{
    this->vao = new ogl_vertex_array_object();

    this->vbo = new ogl_buffer_object(GL_ARRAY_BUFFER);
    vbo->data(sizeof(vertex) * vertices.size(), (void*)vertices.data());

    this->ibo = new ogl_buffer_object(GL_ELEMENT_ARRAY_BUFFER);
    ibo->data(sizeof(unsigned int) * indices.size(), (void*)indices.data());
    this->numindices = indices.size();
}

mesh::mesh()
{
}


mesh::~mesh()
{
    this->clear();
}


void mesh::clear()
{
    for (auto entry : this->_entries) {
        if (entry.vao) delete entry.vao;
        if (entry.vbo) delete entry.vbo;
        if (entry.ibo) delete entry.ibo;
    }
}

const std::vector<mesh::mesh_entry>& mesh::entries() const
{
    return this->_entries;
}

const std::vector<mesh::materials>& mesh::mtls() const
{
    return this->_mtls;
}


bool mesh::load(const std::string& filename)
{
    this->clear();

    bool ret = false;
    Assimp::Importer Importer;

    const aiScene* scene = Importer.ReadFile(filename.c_str(),
                                             aiProcess_Triangulate |
                                             aiProcess_GenSmoothNormals |
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_JoinIdenticalVertices |
                                            aiProcess_FlipUVs);

    if (scene) {
        ret = init_from_scene(scene, filename);
    } else {
        console::error("parsing '%s': '%s'", filename.c_str(), Importer.GetErrorString());
    }

    return ret;
}

bool mesh::init_from_scene(const aiScene* pScene, const std::string& Filename)
{
    this->_entries.resize(pScene->mNumMeshes);
    this->_mtls.resize(pScene->mNumMaterials);

    for (unsigned int i = 0 ; i < _entries.size() ; i++) {
        const aiMesh* paimesh = pScene->mMeshes[i];
        this->init_mesh(i, paimesh);
    }

    return this->init_materials(pScene, Filename);
}

void mesh::init_mesh(unsigned int Index, const aiMesh* paimesh)
{
    this->_entries[Index].material_index = paimesh->mMaterialIndex;

    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0 ; i < paimesh->mNumVertices ; i++) {
        const aiVector3D* pPos      = &(paimesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paimesh->mNormals[i]);
        const aiVector3D* tangent   = &(paimesh->mTangents[i]);
        const aiVector3D* pTexCoord = paimesh->HasTextureCoords(0) ? &(paimesh->mTextureCoords[0][i]) : &Zero3D;

        vertex v;
        v.pos     = vec3(pPos->x, pPos->y, pPos->z);
        v.uv      = vec2(pTexCoord->x, pTexCoord->y);
        v.normal  = vec3(pNormal->x, pNormal->y, pNormal->z);
        v.tangent = vec3(tangent->x, tangent->y, tangent->y);
        vertices.push_back(v);
    }

    for (unsigned int i = 0 ; i < paimesh->mNumFaces ; i++) {
        const aiFace& Face = paimesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        indices.push_back(Face.mIndices[0]);
        indices.push_back(Face.mIndices[1]);
        indices.push_back(Face.mIndices[2]);
    }

    this->_entries[Index].init(vertices, indices);
}

//TODO texture load
bool mesh::init_materials(const aiScene* pScene, const std::string& Filename)
{
    // Extract the directory part from the file name
    std::string::size_type SlashIndex = Filename.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos) {
        Dir = ".";
    } else if (SlashIndex == 0) {
        Dir = "/";
    } else {
        Dir = Filename.substr(0, SlashIndex);
    }

    bool ret = true;

    // Initialize the materials
    for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];
        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;
            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string FullPath = Dir + "/" + Path.data;
                this->_mtls[i].diffuse_map = path_join(Dir, Path.data);
            }
        }
    }
    return ret;
}
