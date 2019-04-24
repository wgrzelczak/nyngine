#pragma once
#include "Preinclude.h"
#include <GLFW\glfw3.h>

namespace ny::Core
{
    struct WindowSettings
    {
        std::string title = "Title";
        u32 width = 800;
        u32 height = 600;
    };

    class Window
    {
    public:
        Window(const WindowSettings& settings = WindowSettings());
        virtual ~Window();
        void Close();
        void Update();

        GLFWwindow* GetNative() const { return m_window; }
        u32 GetWidth() const { return m_data.width; }
        u32 GetHeight() const { return m_data.height; }

    private:
        void RegisterCallbacks();

        GLFWwindow* m_window = nullptr;

        struct WindowData
        {
            std::string title;
            u32 width, height;
            bool VSync;
        } m_data;
    };
} // namespace ny::Core