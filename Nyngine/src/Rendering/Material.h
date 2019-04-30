#pragma once
#include "Preinclude.h"
#include "Shader.h"

namespace ny::Rendering
{
    class Material
    {
    public:
        Material(std::string vertexShader, std::string fragmentShader, std::string texture);
        void Bind(f32* vertices, u32 verticesNum, u32* indices, u32 indiciesNum);
        void Attach() const;
        u32 GetProgramId() const { return m_programId; }
        u32 GetTextureId() const { return m_textureId; }

    private:
        u32 m_programId = 0;
        u32 m_textureId = 0;
        u32 m_vao = 0;
    };
} // namespace ny::Rendering