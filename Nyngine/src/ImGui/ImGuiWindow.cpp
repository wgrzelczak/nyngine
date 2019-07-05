#include "pch.h"
#include "ImGuiWindow.h"

namespace ny::imgui
{
    ImGuiWindow::ImGuiWindow()
    {
    }

    ImGuiWindow::ImGuiWindow(std::string title, Function drawFunction, ImGuiWindowFlags flags, bool isOpen) :
        m_title(title), m_drawFunction(std::move(drawFunction)), m_flags(flags), m_isOpen(isOpen)
    {
    }

    void ImGuiWindow::Draw()
    {
        if (!m_isOpen)
            return;

        if (!ImGui::Begin(m_title.c_str(), &m_isOpen, m_flags))
        {
            ImGui::End();
            return;
        }

        if (m_drawFunction)
            m_drawFunction();

        ImGui::End();
    }
} // namespace ny::imgui