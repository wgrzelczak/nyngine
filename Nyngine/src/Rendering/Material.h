#pragma once
#include "Preinclude.h"
#include "Program.h"

namespace ny::Rendering
{
    class Material
    {
    public:
        Material(std::string vertexShader, std::string fragmentShader, std::string textureFilename);
        ~Material();

        void Bind(f32* vertices, u32 verticesNum, u32* indices, u32 indiciesNum);
        void Attach() const;
        Program* GetProgram() const { return m_program; }
        u32 GetTextureId() const { return m_textureId; }

    private:
        void CreateProgram(std::string vertexShader, std::string fragmentShader);

        Program* m_program = nullptr;
        u32 m_textureId = 0;
        u32 m_vao = 0;
        u32 m_vbo = 0;
        u32 m_ebo = 0;
    };
} // namespace ny::Rendering