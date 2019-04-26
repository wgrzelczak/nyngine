#include "pch.h"
#include "Core.h"
#include "Core/Engine.h"
#include "imgui.h"

namespace ny::Debug
{
    void Core::Draw()
    {
        ImGui::Begin("Test");
        static bool st = false;
        if (ImGui::RadioButton("asd", st)) { st = !st; }

        if (ImGui::Button("Refresh Shader"))
        {
            ny::Core::Engine::GetInstance()->m_renderer->Init();
        }

        ImGui::End();
    }
} // namespace ny::Debug