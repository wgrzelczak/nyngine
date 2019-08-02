#pragma once
#include "Preinclude.h"
#include "Program.h"

namespace ny::Rendering
{
    using MaterialHash = std::pair<std::string, std::string>;
    inline MaterialHash CalcluateMaterialHash(const std::string& vs, const std::string& fs)
    {
        return MaterialHash{vs, fs};
    }

    class MaterialShared
    {
    public:
        MaterialShared(std::string vertexShader, std::string fragmentShader);
        ~MaterialShared();

        void Bind() const;
        Program* GetProgram() const { return m_program; }
        //u32 GetTextureId() const { return m_textureId; }

        const MaterialHash m_hash;

    private:
        void CreateProgram(std::string vertexShader, std::string fragmentShader);

        Program* m_program{nullptr};
        //u32 m_textureId{0};
    };
} // namespace ny::Rendering