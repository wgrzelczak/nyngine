#include "pch.h"
#include "Application.h"
#include "Event\InputEvents.h"
#include "Event\WindowEvents.h"
#include "ImGui\ImGuiLayer.h" //to remove
#include "Input\Input.h"
#include "glad\glad.h" //to remove
namespace ny::Core
{
    Application* Application::m_instance = nullptr;

    Application* Application::GetInstance()
    {
        NY_ASSERT(m_instance, "Application not initialized!!");
        return m_instance;
    }

    Application::Application() :
        m_state(ApplicationState::Init)
    {
    }

    Application::~Application()
    {
    }

    void Application::Exec()
    {
        PreInit();
        Init();
        Run();
        Shutdown();
    }

    void Application::PreInit()
    {
        NY_ASSERT(!m_instance, "Application already initialized!!");
        m_instance = this;

        Log::Init();
    }

    void Application::Init()
    {
        NY_TRACE("Initializing...");

        m_layers.push_back(ApplicationLayer());
        m_layers.push_back(ImGuiLayer());

        m_window = std::make_unique<Window>();

        NY_TRACE("Initialized");
        SetState(ApplicationState::Running);
    }

    void Application::Run()
    {
        while (m_state == ApplicationState::Running)
        {
            glClearColor(0, 1, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            auto updateLayer = [&](auto&& arg) {
                using LayerType = std::decay_t<decltype(arg)>;
                if constexpr (HasUpdate<LayerType>)
                {
                    arg.OnUpdate();
                }
            };

            for (auto& l : m_layers)
            {
                std::visit(updateLayer, l);
            }

            m_window->Update();
        }
    }

    void Application::Shutdown()
    {
        NY_TRACE("Shutting down...");
        m_window->Close();
    }
} // namespace ny::Core