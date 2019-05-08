#include "pch.h"
#include "Mesh.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    Mesh::~Mesh()
    {
        if (m_ebo != 0)
            glDeleteBuffers(1, &m_ebo);
        if (m_vbo != 0)
            glDeleteBuffers(1, &m_vbo);
        if (m_vao != 0)
            glDeleteVertexArrays(1, &m_vao);
    }
    void Mesh::Generate()
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(f32), m_vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(u32), m_indicies.data(), GL_STATIC_DRAW);

        u32 attribsStride = 0;
        attribsStride += sizeof(f32) * 3; //pos
        attribsStride += sizeof(f32) * 3; //color
        attribsStride += sizeof(f32) * 2; //uv

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attribsStride, (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attribsStride, (void*)(3 * 4));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, attribsStride, (void*)(6 * 4));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Mesh::Bind() const
    {
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    }
} // namespace ny::Rendering