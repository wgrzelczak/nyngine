#include "pch.h"
#include "Window.h"
#include "Application.h"
#include "Event\InputEvents.h"
#include "Event\WindowEvents.h"
#include <glad\glad.h>

namespace ny::Core
{
    static void glfwErrorCallback(i32 err, const char* msg)
    {
        NY_ERROR("GLFW Error ({}): {}", err, msg);
    }

    Window::Window(const WindowSettings& settings) :
        m_data{settings.title, settings.width, settings.height}
    {
        i32 result = glfwInit();
        NY_ASSERT(result, "Could not intialize GLFW!");
        glfwSetErrorCallback(glfwErrorCallback);

        m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        NY_ASSERT(status, "Failed to initialize Glad!");

        glfwSetWindowUserPointer(m_window, &m_data);

        RegisterCallbacks();
    }

    Window::~Window()
    {
    }

    void Window::Close()
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void Window::RegisterCallbacks()
    {
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
            IApp->OnEvent<WindowClosedEvent>({});
        });

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
            WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
            windowData.width = width;
            windowData.height = height;

            IApp->OnEvent<WindowResizedEvent>({width, height});
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            switch (action)
            {
            case GLFW_PRESS:
                IApp->OnEvent<KeyPressedEvent>({key, 0});
                break;

            case GLFW_RELEASE:
                IApp->OnEvent<KeyReleasedEvent>({key});
                break;

            case GLFW_REPEAT:
                IApp->OnEvent<KeyPressedEvent>({key, 1});
                break;
            }
        });

        glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode) {
            IApp->OnEvent<KeyTypedEvent>({keycode});
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
            switch (action)
            {
            case GLFW_PRESS:
                IApp->OnEvent<MouseButtonPressedEvent>({button});
                break;

            case GLFW_RELEASE:
                IApp->OnEvent<MouseButtonReleasedEvent>({button});
                break;
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
            IApp->OnEvent<MouseScrolledEvent>({static_cast<f32>(xOffset), static_cast<f32>(yOffset)});
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
            IApp->OnEvent<MouseMovedEvent>({static_cast<f32>(xPos), static_cast<f32>(yPos)});
        });
    }
} // namespace ny::Core