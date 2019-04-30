#include "pch.h"
#include "Renderer.h"
#include "Core/Engine.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    void Renderer::Init()
    {
        Attrib_t attributes = AttributesHelper::GetByType(MaterialType::TextureColorBlend);
        m_material = std::make_shared<Material>(attributes, "Assets/Shaders/default.vs", "Assets/Shaders/default.fs", "Assets/Textures/texture.jpg");

        //TODO
        float vertices[] = {
            -1.f, 1.f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  // top left
            1.f, 1.f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,   // top right
            -1.f, -1.f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left

            1.f, 1.f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
            1.f, -1.f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
            -1.f, -1.f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f // bottom left
        };
        unsigned int indices[] = {
            0, 1, 2,
            3, 4, 5};

        m_material->Bind(vertices, sizeof(vertices), indices, sizeof(indices));
    }

    void Renderer::BeginFrame()
    {
        glClearColor(0.25f, 0.25f, 0.25f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe

        m_material->Attach();
        glUniform1ui(glGetUniformLocation(m_material->GetProgramId(), "time"), ny::Core::Time::DeltaFromStart());

        u32 width = ny::Core::Engine::GetInstance()->GetWindow().GetWidth();
        u32 height = ny::Core::Engine::GetInstance()->GetWindow().GetHeight();

        f32 ratio = width / (f32)height;
        glViewport(0, 0, width, height);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
} // namespace ny::Rendering