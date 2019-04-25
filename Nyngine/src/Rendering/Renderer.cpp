#include "pch.h"
#include "Renderer.h"
#include "Core/Engine.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    void Renderer::Init()
    {
        std::shared_ptr vShader = std::make_shared<Shader>("default.vs", ShaderType::Vertex);
        std::shared_ptr fShader = std::make_shared<Shader>("default.fs", ShaderType::Fragment);

        m_shaders.push_back(vShader);
        m_shaders.push_back(fShader);

        m_programId = glCreateProgram();
        vShader->AttachToProgram(m_programId);
        fShader->AttachToProgram(m_programId);

        glLinkProgram(m_programId);
    }

    void Renderer::BeginFrame()
    {
        //u32 width = ny::Engine::GetInstance()->GetWindow().GetWidth();
        //u32 height = ny::Engine::GetInstance()->GetWindow().GetHeight();

        /*f32 ratio = width / (f32)height;
        glViewport(0, 0, width, height);*/
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
} // namespace ny::Rendering