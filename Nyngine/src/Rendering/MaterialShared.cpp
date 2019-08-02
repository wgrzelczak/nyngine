#include "pch.h"
#include "Material.h"
#include "Texture.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    MaterialShared::MaterialShared(std::string vertexShader, std::string fragmentShader) :
        m_hash(CalcluateMaterialHash(vertexShader, fragmentShader))
    {
        NY_INFO("[Rendering] Creating Material: {}, {}", vertexShader, fragmentShader);
        CreateProgram(std::move(vertexShader), std::move(fragmentShader));
    }

    MaterialShared::~MaterialShared()
    {
        NY_INFO("[Rendering] Destroying Material...");
        m_program.reset();

        if (m_textureId != 0)
            glDeleteTextures(1, &m_textureId);

        NY_INFO("[Rendering] Material has been destroyed");
    }

    void MaterialShared::Bind() const
    {
        if (!m_program) return;

        glUseProgram(m_program->m_programId);

        if (m_textureId != 0)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_textureId);
        }
    }

    void MaterialShared::SetMainTexture(std::string texturePath)
    {
        if (m_textureId != 0)
            glDeleteTextures(1, &m_textureId);

        Texture texture = Texture(std::move(texturePath));
        m_textureId = texture.GetId();
    }

    void MaterialShared::CreateProgram(std::string vertexShader, std::string fragmentShader)
    {
        m_program.reset(new Program(vertexShader, fragmentShader));
    }

} // namespace ny::Rendering