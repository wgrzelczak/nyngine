#include "pch.h"
#include "Material.h"
#include "Texture.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    Material::Material(Attrib_t attribs, std::string vertexShader, std::string fragmentShader, std::string textureFilename) :
        m_attributes(attribs)
    {
        CreateProgram(std::move(vertexShader), std::move(fragmentShader));

        Texture texture = Texture(std::move(textureFilename));
        m_textureId = texture.GetId();
        texture.UnloadData();
    }

    Material::~Material()
    {
        if (m_ebo != 0)
            glDeleteBuffers(1, &m_ebo);
        if (m_vbo != 0)
            glDeleteBuffers(1, &m_vbo);
        if (m_vao != 0)
            glDeleteVertexArrays(1, &m_vao);
    }

    void Material::Bind(f32* vertices, u32 verticesSize, u32* indices, u32 indiciesSize)
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesSize, indices, GL_STATIC_DRAW);

        u32 attribsSize = AttributesHelper::GetAttributesSize(m_attributes);
        u32 attribsOffset = 0;

        if (AttributesHelper::IsAttribSet(m_attributes, Attribute::aPosition))
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attribsSize, (void*)attribsOffset);
            glEnableVertexAttribArray(0);
            attribsOffset += AttributesHelper::GetAttributeSize(Attribute::aPosition);
        }

        if (AttributesHelper::IsAttribSet(m_attributes, Attribute::aColor3))
        {
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attribsSize, (void*)attribsOffset);
            glEnableVertexAttribArray(1);
            attribsOffset += AttributesHelper::GetAttributeSize(Attribute::aColor3);
        }

        if (AttributesHelper::IsAttribSet(m_attributes, Attribute::aTexture0))
        {
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, attribsSize, (void*)attribsOffset);
            glEnableVertexAttribArray(2);
            attribsOffset += AttributesHelper::GetAttributeSize(Attribute::aTexture0);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Material::Attach() const
    {
        glUseProgram(m_programId);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

        glBindTexture(GL_TEXTURE_2D, m_textureId);
    }
    void Material::CreateProgram(std::string vertexShader, std::string fragmentShader)
    {
        Shader vShader = Shader(vertexShader, ShaderType::Vertex);
        Shader fShader = Shader(fragmentShader, ShaderType::Fragment);

        m_programId = glCreateProgram();
        glAttachShader(m_programId, vShader.m_shaderId);
        glAttachShader(m_programId, fShader.m_shaderId);

        glLinkProgram(m_programId);
        Shader::CheckLinkingError(m_programId);

        glDeleteShader(vShader.m_shaderId);
        glDeleteShader(fShader.m_shaderId);
    }
} // namespace ny::Rendering