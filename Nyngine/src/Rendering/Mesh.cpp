#include "pch.h"
#include "Mesh.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<u32> indicies) :
        m_positions(positions), m_indicies(indicies)
    {
        Generate();
    }
    Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uvs, std::vector<u32> indicies) :
        m_positions(positions), m_uvs(uvs), m_indicies(indicies)
    {
        Generate();
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
        u32 attribsOffset = 0;
        u32 attribsStride = 0;
        attribsStride += sizeof(f32) * 3;
        if (m_uvs.size() > 0) attribsStride += sizeof(f32) * 2;

        std::vector<f32> data;
        data.reserve(m_positions.size() * attribsStride);

        for (u32 i{0}; i < m_positions.size(); ++i)
        {
            data.push_back(m_positions.at(i).x);
            data.push_back(m_positions.at(i).y);
            data.push_back(m_positions.at(i).z);

            if (m_uvs.size() > 0)
            {
                data.push_back(m_uvs.at(i).x);
                data.push_back(m_uvs.at(i).y);
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
        if (m_uvs.size() > 0)
        {
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, attribsStride, (void*)attribsOffset);
            glEnableVertexAttribArray(1);
            attribsOffset += 2 * sizeof(f32);
        }

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