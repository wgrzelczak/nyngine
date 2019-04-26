#pragma once
#include "Preinclude.h"
#include "Shader.h"

namespace ny::Rendering
{
    class Material
    {
    public:
        Material(std::string vertexShader, std::string fragmentShader);
        void Attach() const;
        u32 GetId() const { return m_programId; }

    private:
        u32 m_programId = 0;
    };
} // namespace ny::Rendering