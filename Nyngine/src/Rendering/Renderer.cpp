#include "pch.h"
#include "Renderer.h"
#include "Core/Engine.h"
#include "ImGui/ImGuiSystem.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace ny::Rendering
{
    void Renderer::Init()
    {
        NY_INFO("[Rendering] Initialize...");
        RegisterImGuiDebug();

        m_commandBuffer = std::make_unique<CommandBuffer>();

        NY_INFO("[Rendering] Initialized");
    }

    void Renderer::Render(const Camera& camera)
    {
        glClearColor(0.25f, 0.25f, 0.25f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe

        u32 width{ny::Core::Engine::GetInstance()->GetWindow().GetWidth()};
        u32 height{ny::Core::Engine::GetInstance()->GetWindow().GetHeight()};

        f32 ratio{width / (f32)height};
        glViewport(0, 0, width, height);

        glm::mat4 PV{camera.Projection() * camera.View()};

        for (const auto& cmd : m_commandBuffer->GetCommands())
        {
            cmd.m_material->Bind();

            if (m_directionalLight.m_enabled)
            {
                cmd.m_material->GetProgram().SetVector("DirLightPos", m_directionalLight.m_position);
                cmd.m_material->GetProgram().SetVector("DirLightColor", m_directionalLight.m_color);
                cmd.m_material->GetProgram().SetFloat("DirLightAmbientStrength", m_directionalLight.m_ambientStrength);
                cmd.m_material->GetProgram().SetFloat("DirLightSpecularStrength", m_directionalLight.m_specularStrength);
                cmd.m_material->GetProgram().SetUint("DirLightSpecularShininess", m_directionalLight.m_specularShininess);
            }
            else
            {
                cmd.m_material->GetProgram().SetVector("DirLightColor", glm::vec3(1));
                cmd.m_material->GetProgram().SetFloat("DirLightAmbientStrength", 1.0);
            }

            cmd.m_material->GetProgram().SetUint("time", static_cast<u32>(ny::Core::Time::DeltaFromStart()));
            cmd.m_material->GetProgram().SetMatrix("M", (cmd.m_transform));
            cmd.m_material->GetProgram().SetVector("ViewPos", camera.GetPosition());
            cmd.m_material->GetProgram().SetMatrix("MVP", (PV * cmd.m_transform));
            cmd.m_mesh->Bind();

            glDrawElements(GL_TRIANGLES, static_cast<i32>(cmd.m_mesh->m_indicesNum), GL_UNSIGNED_SHORT, 0);
        }
        m_commandBuffer->Clear();
    }

    void Renderer::PushCommand(Command&& cmd)
    {
        m_commandBuffer->PushCommand(std::move(cmd));
    }

    void Renderer::RegisterImGuiDebug()
    {
        auto callback = [this]() -> void {
            if (ImGui::Button("Reinitialize renderer")) Init();

            //Directional light
            if (ImGui::Button("Toggle directional light")) m_directionalLight.m_enabled = !m_directionalLight.m_enabled;
            ImGui::DragFloat3("Directional Light Position", &m_directionalLight.m_position.x);
            ImGui::DragFloat3("Directional Light Color", &m_directionalLight.m_color.x, 0.01f, 0.0f);
            ImGui::DragFloat("Directional Light Ambient Strength", &m_directionalLight.m_ambientStrength, 0.01f);
            ImGui::DragFloat("Directional Light Specular Strength", &m_directionalLight.m_specularStrength, 0.01f);
            ImGui::DragInt("Directional Light Specular Shininess", (i32*)&m_directionalLight.m_specularShininess);
        };

        imgui::RegisterWindow("Renderer", callback);
    }
} // namespace ny::Rendering