#include "pch.h"
#include "Shader.h"
#include "Core/Utilities/Filesystem.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    Shader::Shader(std::string filename, ShaderType type) :
        m_name(std::move(filename)), m_type(type)
    {
        Load();
    }

    u32 Shader::GetGLShaderType(ShaderType shaderType)
    {
        switch (shaderType)
        {
        case ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;
        case ShaderType::Vertex:
            return GL_VERTEX_SHADER;
        }

        NY_ERROR("Undefined shader type!!");
        return -1;
    }

    void Shader::CheckCompilationError(u32 shaderId)
    {
        i32 status;
        char info[1024];
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            glGetShaderInfoLog(shaderId, 1024, NULL, info);
            NY_ERROR("[Shader] Cannot compile shader {}: {}", shaderId, info);
        }
    }

    void Shader::CheckLinkingError(u32 programId)
    {
        i32 status;
        char info[1024];
        glGetProgramiv(programId, GL_LINK_STATUS, &status);
        if (!status)
        {
            glGetProgramInfoLog(programId, 1024, NULL, info);
            NY_ERROR("[Shader] Cannot link program {}: {}", programId, info);
        }
    }

    void Shader::Load()
    {
        std::ifstream in(m_name);

        NY_ASSERT(in.good(), "Cannot open file: {}", m_name);

        std::string shaderCode = Utilities::ReadFileToString(m_name);
        const char* shaderCodePtr = shaderCode.c_str();
        m_shaderId = glCreateShader(GetGLShaderType(m_type));
        glShaderSource(m_shaderId, 1, &shaderCodePtr, NULL);
        glCompileShader(m_shaderId);
        CheckCompilationError(m_shaderId);
    }
} // namespace ny::Rendering