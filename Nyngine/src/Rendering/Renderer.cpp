#include "pch.h"
#include "Renderer.h"
#include "Core/Engine.h"
#include "ImGui/ImGuiSystem.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace ny::Rendering
{
    static glm::quat tmpQuat{1.f, 0.f, 0.f, 0.f};
    static glm::quat tmpQuatN{1.f, 0.f, 0.f, 0.f};

    Renderer::Renderer() :
        m_camera({0, 0, -3.0f}, {0, 0, 1}, {0, 1, 0})
    {
        RegisterImGuiDebug();

        m_commandBuffer = std::make_unique<CommandBuffer>();
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::Init()
    {
        NY_INFO("[Rendering] Initialize...");
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
        tmp_model->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
        //tmp_model->SetQuaternionRotation(glm::quat(0.8f, 0.0f, 0.0f, 0.6f));

        NY_INFO("[Rendering] Initialized");
    }

    void Renderer::Render()
    {
        glClearColor(0.25f, 0.25f, 0.25f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe

        u32 width = ny::Core::Engine::GetInstance()->GetWindow().GetWidth();
        u32 height = ny::Core::Engine::GetInstance()->GetWindow().GetHeight();

        f32 ratio = width / (f32)height;
        glViewport(0, 0, width, height);

        glm::mat4 PV = m_camera.Projection() * m_camera.View();

        //++TMP
        f32 delta = (float)ny::Core::Time::Delta() * 0.0001f;
        tmp_model->AddRotation(tmpQuatN * delta);
        tmp_model->CalculateModelMatrix();
        m_commandBuffer->PushCommand(Command(tmp_model->GetMaterial(), tmp_model->GetMesh(), tmp_model->GetModelMatrix()));
        //--TMP

        for (const auto& cmd : m_commandBuffer->GetCommands())
        {
            cmd.m_material->Bind();
            cmd.m_material->GetProgram()->SetUint("time", ny::Core::Time::DeltaFromStart());
            cmd.m_material->GetProgram()->SetMatrix("MVP", (PV * cmd.m_transform));
            cmd.m_mesh->Bind();

            glDrawElements(GL_TRIANGLES, cmd.m_mesh->m_indicies.size(), GL_UNSIGNED_INT, 0);
        }
        m_commandBuffer->Clear();
    }

    void Renderer::RegisterImGuiDebug()
    {
        ImGuiSystem::RegisterFunction(
            [this]() -> void {
                if (ImGui::Button("Reinitialize renderer")) Init();
                if (ImGui::Button("Reset camera position"))
                {
                    m_camera = {{0, 0, -3.0f}, {0, 0, 1}, {0, 1, 0}};
                    m_camera.SetPerspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
                }
                ImGui::DragFloat3("Camera position", &m_camera.GetPositionRef().x, 0.01f);
                m_camera.UpdateView();
                ImGui::DragFloat4("Model rotation", &tmp_model->GetRotationRef().x, 0.01f);
                tmp_model->NormalizeRotation();
                ImGui::DragFloat4("Rotate0", &tmpQuat.x, 0.0001f, -1.f, 1.f, "%.5f");
                tmpQuatN = glm::normalize(tmpQuat);
                ImGui::DragFloat4("Rotate1", &tmpQuatN.x, 0.01f);
            });
    }
} // namespace ny::Rendering