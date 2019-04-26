#include "pch.h"
#include "Material.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    Material::Material(std::string vertexShader, std::string fragmentShader)
    {
        Shader vShader = Shader(vertexShader, ShaderType::Vertex);
        Shader fShader = Shader(fragmentShader, ShaderType::Fragment);

        m_programId = glCreateProgram();
        glAttachShader(m_programId, vShader.m_shaderId);
        glAttachShader(m_programId, fShader.m_shaderId);

        glLinkProgram(m_programId);

        //checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vShader.m_shaderId);
        glDeleteShader(fShader.m_shaderId);
    }
    void Material::Attach() const
    {
    }
} // namespace ny::Rendering