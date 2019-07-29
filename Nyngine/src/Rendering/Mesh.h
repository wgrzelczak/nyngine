#pragma once
#include "Preinclude.h"
#include "Attributes.h"
#include "glm/glm.hpp"

namespace ny::Rendering
{
    struct Mesh
    {
        struct VertexAttributesSettings
        {
            struct Data
            {
                void* dataPtr{nullptr};
                u32 num{0};
                u8 fieldsNum{0};
                u8 fieldsTypeSize{0};

                inline void* data() const { return dataPtr; }
                inline u32 size() const { return num * fieldsNum * fieldsTypeSize; }
                inline u32 stride() const { return fieldsNum * fieldsTypeSize; }
            };

            Data indices;
            Data positions;
            Data normals;
            Data texcoords;

            Data joints;
            Data weights;

            Data jointsMatrices;
        };

        Mesh();
        Mesh(const VertexAttributesSettings& settings);
        ~Mesh();

        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec3> m_normals;
        std::vector<glm::vec2> m_texcoords;
        std::vector<u32> m_indicies;

        u32 m_vao{0};
        u32 m_vbos[GL_ATTRIB_NUM] = {0};
        u32 m_ebo{0};

        u32 m_indicesNum{0};

        void Generate(VertexAttributesSettings settings);

        void Bind() const;
    };
} // namespace ny::Rendering