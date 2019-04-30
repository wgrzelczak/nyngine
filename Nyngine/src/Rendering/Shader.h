#pragma once
#include "Preinclude.h"

namespace ny::Rendering
{
    enum ShaderType
    {
        Undefined = -1,
        Fragment,
        Vertex
    };

    class Shader
    {
    public:
        Shader(std::string filename, ShaderType type);

        u32 m_shaderId;
        std::string m_name;

        static u32 GetGLShaderType(ShaderType shaderType);

        static void CheckCompilationError(u32 shaderId);
        static void CheckLinkingError(u32 programId);
    };
} // namespace ny::Rendering