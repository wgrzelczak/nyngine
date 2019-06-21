#include "pch.h"
#include "Mesh.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    Mesh::Mesh()
    {
    }

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
        NY_INFO("[Rendering] Creating mesh...");

        u32 attribsOffset = 0;
        u32 attribsStride = 0;
        attribsStride += sizeof(f32) * 3;
        if (m_normals.size() > 0) attribsStride += sizeof(f32) * 3;
        if (m_texcoords.size() > 0) attribsStride += sizeof(f32) * 2;

        std::vector<f32> data;
        data.reserve(m_positions.size() * attribsStride);

        for (u32 i{0}; i < m_positions.size(); ++i)
        {
            data.push_back(m_positions.at(i).x);
            data.push_back(m_positions.at(i).y);
            data.push_back(m_positions.at(i).z);

            if (m_normals.size() > 0)
            {
                data.push_back(m_normals.at(i).x);
                data.push_back(m_normals.at(i).y);
                data.push_back(m_normals.at(i).z);
            }

            if (m_texcoords.size() > 0)
            {
                data.push_back(m_texcoords.at(i).x);
                data.push_back(m_texcoords.at(i).y);
            }
        }

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(f32), data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(u32), m_indicies.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attribsStride, (void*)attribsOffset);
        glEnableVertexAttribArray(0);
        attribsOffset += 3 * sizeof(f32);

        if (m_normals.size() > 0)
        {
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attribsStride, (void*)attribsOffset);
            glEnableVertexAttribArray(1);
            attribsOffset += 3 * sizeof(f32);
        }

        if (m_texcoords.size() > 0)
        {
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, attribsStride, (void*)attribsOffset);
            glEnableVertexAttribArray(2);
            attribsOffset += 2 * sizeof(f32);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        NY_INFO("[Rendering] Mesh created, Positions: {}, Normals: {}, UVs: {}, Indicies: {}", m_positions.size(), m_normals.size(), m_texcoords.size(), m_indicies.size());
    }

    void Mesh::Bind() const
    {
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    }
} // namespace ny::Rendering