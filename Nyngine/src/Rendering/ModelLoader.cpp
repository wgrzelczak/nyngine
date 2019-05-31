#include "pch.h"
#include "ModelLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace ny::Rendering::ModelLoader
{
    struct tinobjloaderMesh
    {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texcoords;
        std::vector<u32> v_indices;
        std::vector<u32> vn_indices;
        std::vector<u32> vt_indices;

        std::vector<tinyobj::material_t> materials;
    };

    void vertex_cb(void* user_data, float x, float y, float z, float w)
    {
        tinobjloaderMesh* mesh = reinterpret_cast<tinobjloaderMesh*>(user_data);
        NY_DEBUG("v[{}] = {}, {}, {}", mesh->vertices.size(), x, y, z, w);

        mesh->vertices.push_back({x, y, z});
        // Discard w
    }

    void normal_cb(void* user_data, float x, float y, float z)
    {
        tinobjloaderMesh* mesh = reinterpret_cast<tinobjloaderMesh*>(user_data);
        NY_DEBUG("vn[{}] = {}, {}, {}", mesh->normals.size(), x, y, z);

        mesh->normals.push_back({x, y, z});
    }

    void texcoord_cb(void* user_data, float x, float y, float z)
    {
        tinobjloaderMesh* mesh = reinterpret_cast<tinobjloaderMesh*>(user_data);
        NY_DEBUG("vt[{}] = {}, {}, {}", mesh->texcoords.size(), x, y, z);

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
            NY_DEBUG("(Need fixIndex()) idx[{}] = {}, {}, {}", mesh->v_indices.size(), idx.vertex_index, idx.normal_index, idx.texcoord_index);

            int tmp = 0;

            tinyobj::fixIndex(idx.vertex_index, num_indices, &tmp);
            mesh->v_indices.push_back(tmp);

            tinyobj::fixIndex(idx.normal_index, num_indices, &tmp);
            mesh->vn_indices.push_back(tmp);

            tinyobj::fixIndex(idx.texcoord_index, num_indices, &tmp);
            //mesh->vt_indices.push_back(tmp);
        }
    }

    void usemtl_cb(void* user_data, const char* name, int material_idx)
    {
        tinobjloaderMesh* mesh = reinterpret_cast<tinobjloaderMesh*>(user_data);
        if ((material_idx > -1) && (material_idx < mesh->materials.size()))
        {
            printf("usemtl. material id = %d(name = %s)\n", material_idx,
                   mesh->materials[material_idx].name.c_str());
        }
        else
        {
            printf("usemtl. name = %s\n", name);
        }
    }

    void mtllib_cb(void* user_data, const tinyobj::material_t* materials, int num_materials)
    {
        tinobjloaderMesh* mesh = reinterpret_cast<tinobjloaderMesh*>(user_data);
        printf("mtllib. # of materials = %d\n", num_materials);

        for (int i = 0; i < num_materials; i++)
        {
            mesh->materials.push_back(materials[i]);
        }
    }

    void group_cb(void* user_data, const char** names, int num_names)
    {
        // MyMesh *mesh = reinterpret_cast<MyMesh*>(user_data);
        printf("group : name = \n");

        for (int i = 0; i < num_names; i++)
        {
            printf("  %s\n", names[i]);
        }
    }

    void object_cb(void* user_data, const char* name)
    {
        // MyMesh *mesh = reinterpret_cast<MyMesh*>(user_data);
        printf("object : name = %s\n", name);
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
        mesh->m_indicies.swap(tolMesh.v_indices);

        mesh->m_positions.clear();
        mesh->m_positions.swap(tolMesh.vertices);

        mesh->m_uvs.clear();
        mesh->m_uvs.swap(tolMesh.texcoords);
    }
} // namespace ny::Rendering::ModelLoader