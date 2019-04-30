#include "pch.h"
#include "Core.h"
#include "Core/Engine.h"
#include "imgui.h"

namespace ny::Debug
{
    void Core::Draw()
    {
        ImGui::Begin("Test");

        if (ImGui::Button("Reinitialize renderer"))
        {
            ny::Core::Engine::GetInstance()->m_renderer->Init();
        }

        ImGui::End();
    }
} // namespace ny::Debug