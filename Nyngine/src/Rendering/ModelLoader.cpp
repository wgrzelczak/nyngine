#include "pch.h"
#include "ModelLoader.h"

namespace ny::Rendering::ModelLoader
{
    struct objFace
    {
        i32 vertexIndex;
        i32 texcoordIndex;
        i32 normalIndex;
    };

    struct objMesh
    {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> texcoords;
        std::vector<glm::vec3> normals;
        std::vector<objFace> faces;
    };

    void LoadObj(Mesh& mesh, std::string filename)
    {
        NY_WARN("Loading meshes not implemented! Loaded default mesh");

        // clang-format off
        objMesh obj;
        obj.vertices =
        {
            { -0.500000, -0.500000, 0.500000 },
            { 0.500000, -0.500000, 0.500000 },
            { -0.500000, 0.500000, 0.500000 },
            { 0.500000, 0.500000, 0.500000 },
            { -0.500000, 0.500000, -0.500000 },
            { 0.500000, 0.500000, -0.500000 },
            { -0.500000, -0.500000, -0.500000 },
            { 0.500000, -0.500000, -0.500000 }
        };

        obj.normals =
        {
            { 0.000000, 0.000000, 1.000000 },
            { 0.000000, 1.000000, 0.000000 },
            { 0.000000, 0.000000, -1.000000 },
            { 0.000000, -1.000000, 0.000000 },
            { 1.000000, 0.000000, 0.000000 },
            { -1.000000, 0.000000, 0.000000 }
        };

        obj.texcoords =
        {
            { 0.000000, 0.000000 },
            { 1.000000, 0.000000 },
            { 0.000000, 1.000000 },
            { 1.000000, 1.000000 }
        };

        obj.faces =
        {
            { 1,1,1 },{ 2,2,1 },{ 3,3,1 },
            { 3,3,1 },{ 2,2,1 },{ 4,4,1 },
            { 3,1,2 },{ 4,2,2 },{ 5,3,2 },
            { 5,3,2 },{ 4,2,2 },{ 6,4,2 },
            { 5,4,3 },{ 6,3,3 },{ 7,2,3 },
            { 7,2,3 },{ 6,3,3 },{ 8,1,3 },
            { 7,1,4 },{ 8,2,4 },{ 1,3,4 },
            { 1,3,4 },{ 8,2,4 },{ 2,4,4 },
            { 2,1,5 },{ 8,2,5 },{ 4,3,5 },
            { 4,3,5 },{ 8,2,5 },{ 6,4,5 },
            { 7,1,6 },{ 1,2,6 },{ 5,3,6 },
            { 5,3,6 },{ 1,2,6 },{ 3,4,6 }
        };
        // clang-format on

        mesh.m_indicies.clear();
        mesh.m_positions.clear();
        mesh.m_uvs.clear();

        u32 index = 0;
        for (const auto& f : obj.faces)
        {
            mesh.m_positions.push_back(obj.vertices.at(f.vertexIndex - 1));
            if (obj.texcoords.size() > 0)
            {
                mesh.m_uvs.push_back(obj.texcoords.at(f.texcoordIndex - 1));
            }
            //mesh.m_texcoords.push_back(obj.normals.at(f.normalIndex - 1));

            //TODO: proper dealing with indices (hash vertexIndex, normalIndex and texcoordIndex and deduplicate)
            mesh.m_indicies.push_back(index);
            index++;
        }

        mesh.Generate();
    }
} // namespace ny::Rendering::ModelLoader