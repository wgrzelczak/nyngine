#pragma once
#include "Attributes.h"
#include "Preinclude.h"
#include "Shader.h"

namespace ny::Rendering
{
    class Material
    {
    public:
        Material(Attrib_t attribs, std::string vertexShader, std::string fragmentShader, std::string textureFilename);
        Material(MaterialType type, std::string vertexShader, std::string fragmentShader, std::string textureFilename);
        ~Material();

        void Bind(f32* vertices, u32 verticesNum, u32* indices, u32 indiciesNum);
        void Attach() const;
        u32 GetProgramId() const { return m_programId; }
        u32 GetTextureId() const { return m_textureId; }

    private:
        void CreateProgram(std::string vertexShader, std::string fragmentShader);

        u32 m_programId = 0;
        u32 m_textureId = 0;
        u32 m_vao = 0;
        u32 m_vbo = 0;
        u32 m_ebo = 0;

        Attrib_t m_attributes = 0;
    };
} // namespace ny::Rendering