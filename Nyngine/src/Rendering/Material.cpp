#include "pch.h"
#include "Material.h"
#include "Texture.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    Material::Material(std::string vertexShader, std::string fragmentShader, std::string textureFilename)
    {
        NY_INFO("[Rendering] Creating Material: {}, {}", vertexShader, fragmentShader);
        CreateProgram(std::move(vertexShader), std::move(fragmentShader));

        Texture texture = Texture(std::move(textureFilename));
        m_textureId = texture.GetId();
    }

    Material::~Material()
    {
        NY_INFO("[Rendering] Destroying Material...");
        if (m_program != nullptr)
            delete m_program;
        NY_INFO("[Rendering] Material has been destroyed");
    }

    void Material::Bind() const
    {
        Program* program = GetProgram();
        if (!program) return;

        glUseProgram(program->m_programId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
    }

    void Material::CreateProgram(std::string vertexShader, std::string fragmentShader)
    {
        //m_program = std::make_unique<Program>(vertexShader, fragmentShader);
        if (m_program != nullptr) delete m_program;
        m_program = new Program(vertexShader, fragmentShader);
    }

} // namespace ny::Rendering