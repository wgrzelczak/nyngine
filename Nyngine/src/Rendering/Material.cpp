#include "pch.h"
#include "Material.h"
#include "Texture.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    Material::Material(std::string vertexShader, std::string fragmentShader, std::string textureFilename)
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

        glGenTextures(1, &m_textureId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Texture texture = Texture(std::move(textureFilename));
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.m_width, texture.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.m_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void Material::Bind(f32* vertices, u32 verticesSize, u32* indices, u32 indiciesSize)
    {
        unsigned int VBO, EBO;
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesSize, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Material::Attach() const
    {
        glUseProgram(m_programId);
        glBindVertexArray(m_vao);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
    }
} // namespace ny::Rendering