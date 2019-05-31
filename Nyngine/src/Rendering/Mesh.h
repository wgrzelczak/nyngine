#pragma once
#include "Preinclude.h"
#include "glm/glm.hpp"

namespace ny::Rendering
{
    struct Mesh
    {
        Mesh();
        Mesh(std::vector<glm::vec3> positions, std::vector<u32> indicies);
        Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uvs, std::vector<u32> indicies);
        ~Mesh();

        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec2> m_uvs;
        std::vector<u32> m_indicies;

        u32 m_vao = 0;
        u32 m_vbo = 0;
        u32 m_ebo = 0;

        void Generate();
        void Bind() const;
    };
} // namespace ny::Rendering