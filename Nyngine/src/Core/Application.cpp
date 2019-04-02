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

    void Application::PreInit()
    {
        NY_ASSERT(!m_instance, "Application already initialized!!");
        m_instance = this;

        Time::Init();
        Log::Init();
    }

    void Application::Init()
    {
        NY_TRACE("Initializing...");

        m_window = std::make_unique<Window>();

        PushLayer<ApplicationLayer>();
        PushLayer<ImGuiLayer>();

        NY_TRACE("Initialized");
        SetState(ApplicationState::Running);
    }

    void Application::Run()
    {
        while (m_state == ApplicationState::Running)
        {
            Time::Update();

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
                std::visit(updateLayer, *l);
            }

            m_window->Update();

            NY_DEBUG("FPS: {}", 1000000.0f / Time::Delta());
        }
    }

    void Application::Shutdown()
    {
        NY_TRACE("Shutting down...");
        m_window->Close();
    }

    void Application::SleepFor(u32 milliseconds) const
    {
        std::this_thread::sleep_for(Time::GetDuration(milliseconds));
    }
} // namespace ny::Core