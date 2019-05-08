#pragma once
#include "Preinclude.h"

namespace ny::Rendering
{
    struct Mesh
    {
        ~Mesh();

        std::vector<f32> m_vertices;
        std::vector<u32> m_indicies;

        u32 m_vao = 0;
        u32 m_vbo = 0;
        u32 m_ebo = 0;

        void Generate();
        void Bind() const;
    };
} // namespace ny::Rendering