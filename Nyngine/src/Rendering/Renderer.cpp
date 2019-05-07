#include "pch.h"
#include "Renderer.h"
#include "Core/Engine.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace ny::Rendering
{
    Renderer::Renderer() :
        m_camera({0, 0, -3.0f}, {0, 0, 1}, {0, 1, 0})
    {
    }

    void Renderer::Init()
    {
        m_camera.SetPerspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);

        m_material = std::make_shared<Material>("Assets/Shaders/default.vs", "Assets/Shaders/default.fs", "Assets/Textures/texture.jpg");

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

        u32 width = ny::Core::Engine::GetInstance()->GetWindow().GetWidth();
        u32 height = ny::Core::Engine::GetInstance()->GetWindow().GetHeight();

        f32 ratio = width / (f32)height;
        glViewport(0, 0, width, height);

        glm::mat4 PV = m_camera.Projection() * m_camera.View();

        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, {0, 1, 0});
        model = glm::rotate(model, (float)ny::Core::Time::DeltaFromStart() * 0.000001f, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));

        m_material->Attach();

        m_material->GetProgram()->SetUint("time", ny::Core::Time::DeltaFromStart());
        m_material->GetProgram()->SetMatrix("MVP", (PV * model));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
} // namespace ny::Rendering