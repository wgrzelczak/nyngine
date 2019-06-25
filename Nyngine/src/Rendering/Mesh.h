#pragma once
#include "Preinclude.h"
#include "glm/glm.hpp"

namespace ny::Rendering
{
    struct Mesh
    {
        struct VertexAttributesSettings
        {
            u8 m_indicesStride{0};
            u32 m_indicesNum{0};
            void* p_indices{nullptr};

            u8 m_positionsStride{0};
            u32 m_positionsNum{0};
            void* p_positions{nullptr};
        };

        Mesh();
        ~Mesh();

        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec3> m_normals;
        std::vector<glm::vec2> m_texcoords;
        std::vector<u32> m_indicies;

        u32 m_vao{0};
        u32 m_vbo{0};
        u32 m_ebo{0};

        u32 m_indicesNum{0};

        void Generate();
        void Generate(VertexAttributesSettings settings);

        void Bind() const;
    };
} // namespace ny::Rendering