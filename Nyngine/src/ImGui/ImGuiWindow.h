#pragma once
#include "Preinclude.h"
#include "imgui_bridge.h"

namespace ny::imgui
{
    class ImGuiWindow
    {
    public:
        ImGuiWindow();
        ImGuiWindow(std::string title, Function drawFunction, ImGuiWindowFlags flags, bool isOpen);
        void Draw();

        std::string m_title{"Untitled"};
        bool m_isOpen{false};
        ImGuiWindowFlags m_flags{0};
        Function m_drawFunction{nullptr};
    };
} // namespace ny::imgui