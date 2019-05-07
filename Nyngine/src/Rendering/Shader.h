#pragma once
#include "Attributes.h"
#include "Preinclude.h"
#include "glm/glm.hpp"

namespace ny::Rendering
{
    enum class ShaderType
    {
        Undefined = -1,
        Fragment,
        Vertex
    };

    class Shader
    {
    public:
        static u32 GetGLShaderType(ShaderType shaderType);
        static void CheckCompilationError(u32 shaderId);
        static void CheckLinkingError(u32 programId);

        Shader(std::string filename, ShaderType type);

        u32 m_shaderId;
        std::string m_name;
        ShaderType m_type;

    private:
        void Load();
    };
} // namespace ny::Rendering