#include "pch.h"
#include "Material.h"
#include "Texture.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    Material::Material(std::string vertexShader, std::string fragmentShader, std::string textureFilename)
    {
        CreateProgram(std::move(vertexShader), std::move(fragmentShader));

        Texture texture = Texture(std::move(textureFilename));
        m_textureId = texture.GetId();
    }

    Material::~Material()
    {
        if (m_program != nullptr)
            delete m_program;

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

    void Material::Attach() const
    {
        Program* program = GetProgram();
        if (!program) return;

        glUseProgram(program->m_programId);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

        glBindTexture(GL_TEXTURE_2D, m_textureId);
    }

    void Material::CreateProgram(std::string vertexShader, std::string fragmentShader)
    {
        //m_program = std::make_unique<Program>(vertexShader, fragmentShader);
        if (m_program != nullptr) delete m_program;
        m_program = new Program(vertexShader, fragmentShader);
    }

} // namespace ny::Rendering