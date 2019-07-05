#pragma once
#include "Preinclude.h"
//#include "imgui_bridge.h"
#include "ImGuiWindow.h"

namespace ny::imgui
{
    void RegisterFunction(Function drawFunction);
    void RegisterWindow(std::string name, Function drawFunction, bool isOpened = false);

    class ImGuiSystem
    {
    public:
        static ImGuiSystem* GetInstance();
        ~ImGuiSystem();

        void Update();
        void Clear();

        void RegisterFunction(Function drawFunction);
        void RegisterWindow(ImGuiWindow window);

    private:
        ImGuiSystem();

        void InitCore();

        void NewFrame();
        void EndFrame();

        void DrawMainWindow();
        void DrawWindows();

        void MainWindowDrawFunction();

        std::unique_ptr<ImGuiWindow> m_mainWindow{nullptr};
        std::vector<Function> m_drawFunctions;
        std::vector<ImGuiWindow> m_windows;
    };
} // namespace ny::imgui