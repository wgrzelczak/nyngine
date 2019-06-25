#include "pch.h"
#include "Mesh.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    Mesh::Mesh()
    {
    }

    Mesh::Mesh(const VertexAttributesSettings& settings)
    {
        Generate(settings);
    }

    Mesh::~Mesh()
    {
        for (u32 i{0}; i < GL_ATTRIB_NUM; ++i)
        {
            if (m_vbos[i] != 0)
                glDeleteBuffers(1, &m_vbos[i]);
        }

        if (m_ebo != 0)
            glDeleteBuffers(1, &m_ebo);
        if (m_vao != 0)
            glDeleteVertexArrays(1, &m_vao);
    }

    void Mesh::Generate(VertexAttributesSettings settings)
    {
        glGenVertexArrays(1, &m_vao);

        glBindVertexArray(m_vao);

        //Indices
        m_indicesNum = settings.indices.num;
        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, settings.indices.size(), settings.indices.data(), GL_STATIC_DRAW);

        auto BindAttrib = [&](u32 location, VertexAttributesSettings::Data& data) {
            if (data.data() == nullptr)
                return;

            glGenBuffers(1, &m_vbos[location]);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbos[location]);
            glBufferData(GL_ARRAY_BUFFER, data.size(), data.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(location, data.fieldsNum, GL_FLOAT, GL_FALSE, data.stride(), (void*)(0));
            glEnableVertexAttribArray(location);
        };

        //Positions
        BindAttrib(GL_ATTRIB_LOCATION_POSITION, settings.positions);

        //Texcoords
        BindAttrib(GL_ATTRIB_LOCATION_TEXCOORDS0, settings.texcoords);

        //Normals
        BindAttrib(GL_ATTRIB_LOCATION_NORMALS, settings.normals);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Mesh::Bind() const
    {
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    }
} // namespace ny::Rendering