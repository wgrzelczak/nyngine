#include "pch.h"
#include "ModelLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#define DEBUG_LOADING (0)

namespace ny::Rendering::ModelLoader
{
    struct face
    {
        i32 vertexIndex;
        i32 normalIndex;
        i32 texcoordIndex;
    };

    struct tinobjloaderMesh
    {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texcoords;
        std::vector<face> faces;

        std::vector<tinyobj::material_t> materials;
    };

    void vertex_cb(void* user_data, float x, float y, float z, float w)
    {
        tinobjloaderMesh* mesh = reinterpret_cast<tinobjloaderMesh*>(user_data);
#if DEBUG_LOADING
        NY_DEBUG("v[{}] = {}, {}, {}", mesh->vertices.size(), x, y, z, w);
#endif
        mesh->vertices.push_back({x, y, z});
        // Discard w
    }

    void normal_cb(void* user_data, float x, float y, float z)
    {
        tinobjloaderMesh* mesh = reinterpret_cast<tinobjloaderMesh*>(user_data);
#if DEBUG_LOADING
        NY_DEBUG("vn[{}] = {}, {}, {}", mesh->normals.size(), x, y, z);
#endif
        mesh->normals.push_back({x, y, z});
    }

    void texcoord_cb(void* user_data, float x, float y, float z)
    {
        tinobjloaderMesh* mesh = reinterpret_cast<tinobjloaderMesh*>(user_data);
#if DEBUG_LOADING
        NY_DEBUG("vt[{}] = {}, {}, {}", mesh->texcoords.size(), x, y, z);
#endif
        mesh->texcoords.push_back({x, y});
        // Discrad z
    }

    void index_cb(void* user_data, tinyobj::index_t* indices, int num_indices)
    {
        // NOTE: the value of each index is raw value.
        // For example, the application must manually adjust the index with offset
        // (e.g. v_indices.size()) when the value is negative(whic means relative
        // index).
        // Also, the first index starts with 1, not 0.
        // See fixIndex() function in tiny_obj_loader.h for details.
        // Also, 0 is set for the index value which
        // does not exist in .obj
        tinobjloaderMesh* mesh = reinterpret_cast<tinobjloaderMesh*>(user_data);

        for (int i = 0; i < num_indices; i++)
        {
            tinyobj::index_t idx = indices[i];
#if DEBUG_LOADING
            NY_DEBUG("(Need fixIndex()) face[{}] = {}, {}, {}", mesh->faces.size(), idx.vertex_index, idx.normal_index, idx.texcoord_index);
#endif
            int vertexIndex = 0;
            int normalIndex = 0;
            int texcoordIndex = 0;

            tinyobj::fixIndex(idx.vertex_index, num_indices, &vertexIndex);
            tinyobj::fixIndex(idx.normal_index, num_indices, &normalIndex);
            tinyobj::fixIndex(idx.texcoord_index, num_indices, &texcoordIndex);

            mesh->faces.push_back({vertexIndex, num_indices, texcoordIndex});
        }
    }

    void usemtl_cb(void* user_data, const char* name, int material_idx)
    {
#if DEBUG_LOADING
        tinobjloaderMesh* mesh = reinterpret_cast<tinobjloaderMesh*>(user_data);
        if ((material_idx > -1) && (material_idx < mesh->materials.size()))
        {
            NY_DEBUG("usemtl. material id = {}(name = {})", material_idx, mesh->materials[material_idx].name.c_str());
        }
        else
        {
            NY_DEBUG("usemtl. name = {}", name);
        }
#endif
    }

    void mtllib_cb(void* user_data, const tinyobj::material_t* materials, int num_materials)
    {
        tinobjloaderMesh* mesh = reinterpret_cast<tinobjloaderMesh*>(user_data);
#if DEBUG_LOADING
        NY_DEBUG("mtllib. # of materials = {}", num_materials);
#endif

        for (int i = 0; i < num_materials; i++)
        {
            mesh->materials.push_back(materials[i]);
        }
    }

    void group_cb(void* user_data, const char** names, int num_names)
    {
#if DEBUG_LOADING
        NY_DEBUG("group : name = ");
        for (int i = 0; i < num_names; i++)
        {
            NY_DEBUG("  {}", names[i]);
        }
#endif
    }

    void object_cb(void* user_data, const char* name)
    {
#if DEBUG_LOADING
        NY_DEBUG("object : name = {}", name);
#endif
    }

    void LoadModel(Model& model, std::string filename)
    {
        tinyobj::callback_t cb;
        cb.vertex_cb = vertex_cb;
        cb.normal_cb = normal_cb;
        cb.texcoord_cb = texcoord_cb;
        cb.index_cb = index_cb;
        //cb.usemtl_cb = usemtl_cb;
        cb.mtllib_cb = mtllib_cb;
        cb.group_cb = group_cb;
        cb.object_cb = object_cb;

        std::string warn;
        std::string err;
        std::ifstream ifs(filename.c_str());
        NY_ASSERT(!ifs.fail(), "Cannot find file: {}!", filename);

        tinyobj::MaterialFileReader mtlReader("../../models/");

        tinobjloaderMesh tolMesh;

        bool ret = tinyobj::LoadObjWithCallback(ifs, cb, &tolMesh, &mtlReader, &warn, &err);

        if (!warn.empty())
        {
            NY_WARN("[LoadModel] Warning: {}", warn)
        }

        if (!err.empty())
        {
            NY_ERROR("[LoadModel] Error: {}", err);
        }

        if (!ret)
        {
            NY_ERROR("[LoadModel] Error: Failed to parse {}", filename);
        }

        auto mesh = model.GetMesh();
        NY_ASSERT(mesh, "Error! Model should have a mesh!");

        mesh->m_indicies.clear();
        mesh->m_positions.clear();
        mesh->m_uvs.clear();

        u32 index = 0;
        for (const auto& f : tolMesh.faces)
        {
            mesh->m_positions.push_back(tolMesh.vertices.at(f.vertexIndex));
            if (tolMesh.texcoords.size() > 0)
            {
                mesh->m_uvs.push_back(tolMesh.texcoords.at(f.texcoordIndex));
            }
            //mesh->m_texcoords.push_back(tolMesh.normals.at(f.texcoordIndex));

            //TODO: proper dealing with indices (hash vertexIndex, normalIndex and texcoordIndex and deduplicate)
            mesh->m_indicies.push_back(index);
            index++;
        }
    }
} // namespace ny::Rendering::ModelLoader