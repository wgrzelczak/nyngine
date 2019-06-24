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

        void Bind() const;
        Program* GetProgram() const { return m_program; }
        u32 GetTextureId() const { return m_textureId; }

    private:
        void CreateProgram(std::string vertexShader, std::string fragmentShader);

        Program* m_program{nullptr};
        u32 m_textureId{0};
    };
} // namespace ny::Rendering