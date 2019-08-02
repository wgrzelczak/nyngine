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

        //Texture texture = Texture(std::move(textureFilename));
        //m_textureId = texture.GetId();
    }

    MaterialShared::~MaterialShared()
    {
        NY_INFO("[Rendering] Destroying Material...");
        if (m_program != nullptr)
            delete m_program;
        NY_INFO("[Rendering] Material has been destroyed");
    }

    void MaterialShared::Bind() const
    {
        if (!m_program) return;

        glUseProgram(m_program->m_programId);
        //glBindTexture(GL_TEXTURE_2D, m_textureId);
    }

    void MaterialShared::CreateProgram(std::string vertexShader, std::string fragmentShader)
    {
        //m_program = std::make_unique<Program>(vertexShader, fragmentShader);
        if (m_program != nullptr) delete m_program;
        m_program = new Program(vertexShader, fragmentShader);
    }

} // namespace ny::Rendering