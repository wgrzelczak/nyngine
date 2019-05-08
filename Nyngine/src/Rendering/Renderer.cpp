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
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::Init()
    {
        m_camera.SetPerspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);

        m_material = std::make_shared<Material>("Assets/Shaders/default.vs", "Assets/Shaders/default.fs", "Assets/Textures/texture.jpg");

        std::vector<glm::vec3> positions = {
            {-1.f, 1.f, 1.f},
            {1.f, 1.f, 1.f},
            {-1.f, -1.f, 1.f},
            {1.f, -1.f, 1.f},

            {-1.f, 1.f, -1.f},
            {1.f, 1.f, -1.f},
            {-1.f, -1.f, -1.f},
            {1.f, -1.f, -1.f}};

        std::vector<glm::vec2> uvs = {
            {0.0f, 1.0f},
            {1.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f},

            {0.0f, 1.0f},
            {1.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f}};

        std::vector<u32> indicies = {
            0, 1, 2, 1, 3, 2, //front
            4, 5, 6, 5, 7, 6, //back

            0, 1, 4, 1, 4, 5, //up
            2, 6, 3, 6, 3, 7, //down

            0, 2, 4, 2, 4, 6, //left
            1, 3, 5, 3, 5, 7  //right
        };
        tmp_mesh = new Mesh(positions, uvs, indicies);

        tmp_model = new Model(m_material.get(), tmp_mesh);
        tmp_model->SetPosition(glm::vec3{0, 0, 0});
        tmp_model->SetRotationAroundAxis(glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        tmp_model->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
    }

    void Renderer::BeginFrame()
    {
        glClearColor(0.25f, 0.25f, 0.25f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe

        u32 width = ny::Core::Engine::GetInstance()->GetWindow().GetWidth();
        u32 height = ny::Core::Engine::GetInstance()->GetWindow().GetHeight();

        f32 ratio = width / (f32)height;
        glViewport(0, 0, width, height);

        glm::mat4 PV = m_camera.Projection() * m_camera.View();

        f32 angle = (float)ny::Core::Time::DeltaFromStart() * 0.000001f;
        tmp_model->SetRotationAroundAxis(angle, glm::vec3(1.0f, 1.0f, 1.0f));
        tmp_model->CalculateModelMatrix();

        tmp_model->GetMesh()->Bind();

        m_material->Bind();
        m_material->GetProgram()->SetUint("time", ny::Core::Time::DeltaFromStart());
        m_material->GetProgram()->SetMatrix("MVP", (PV * tmp_model->GetModelMatrix()));

        glDrawElements(GL_TRIANGLES, tmp_model->GetMesh()->m_indicies.size(), GL_UNSIGNED_INT, 0);
    }
} // namespace ny::Rendering