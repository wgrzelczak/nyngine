#include "pch.h"
#include "Shader.h"
#include "Core/Utilities/Filesystem.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    Shader::Shader(std::string filename, ShaderType type) :
        m_name(std::move(filename))
    {
        std::ifstream in(m_name);

        NY_ASSERT(in.good(), "Cannot open file: {}", m_name);

        std::string shaderCode = Utilities::ReadFileToString(m_name);
        const char* shaderCodePtr = shaderCode.c_str();
        m_shader = glCreateShader(GetGLShaderType(type));
        glShaderSource(m_shader, 1, &shaderCodePtr, NULL);
        glCompileShader(m_shader);
    }

    u32 Shader::GetGLShaderType(ShaderType shaderType)
    {
        switch (shaderType)
        {
        case Fragment:
            return GL_FRAGMENT_SHADER;
        case Vertex:
            return GL_VERTEX_SHADER;
        }

        NY_ERROR("Undefined shader type!!");
        return -1;
    }

    void Shader::AttachToProgram(u32 programId)
    {
        glAttachShader(programId, m_shader);
    }
} // namespace ny::Rendering