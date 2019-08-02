#include "pch.h"
#include "Engine.h"
#include "Application.h"
#include "ECS\Ecs.h"
#include "ImGui\ImGuiSystem.h"

namespace ny::Core
{
    Engine* Engine::GetInstance()
    {
        static Engine instance;
        return &instance;
    }

    i32 Engine::Run(Application* app)
    {
        NY_ASSERT(!m_app, "Application has beed initialized already!!");

        Log::Init("Core");

        NY_ASSERT(app, "Application does not exist!!");
        m_app.reset(app);

        Init();

        while (m_state == State::Running)
        {
            Tick();
        }

        Shutdown();

        return ErrorCode::Success;
    }

    void Engine::Init()
    {
        Time::Init();

        m_window = std::make_unique<Window>();
        m_materialManager = std::make_unique<MaterialManager>();
        m_renderer = std::make_unique<Renderer>();
        m_renderer->Init();

        m_app->PreInit();
        m_app->Init();
        m_app->LateInit();

        m_state = State::Running;
    }

    void Engine::Invoke(Event& e)
    {
        NY_ASSERT(m_app, "");

        auto DispatchEvent = [&](auto&& listener) {
            EVENT_DISPATCH(listener, e, MouseMovedEvent);
            EVENT_DISPATCH(listener, e, MouseButtonPressedEvent);
            EVENT_DISPATCH(listener, e, MouseButtonReleasedEvent);
            EVENT_DISPATCH(listener, e, MouseScrolledEvent);

            EVENT_DISPATCH(listener, e, KeyPressedEvent);
            EVENT_DISPATCH(listener, e, KeyReleasedEvent);
            EVENT_DISPATCH(listener, e, KeyTypedEvent);

            EVENT_DISPATCH(listener, e, WindowResizedEvent);
            EVENT_DISPATCH(listener, e, WindowClosedEvent);
        };

        DispatchEvent(*this);
        DispatchEvent(m_app);
    }

    void Engine::OnEvent(WindowClosedEvent& e)
    {
        SetState(State::ShuttingDown);
    }

    void Engine::Tick()
    {
        NY_ASSERT(m_app, "");

        Time::Update();

        imgui::ImGuiSystem::GetInstance()->Update();

        m_app->Tick();

        m_window->Update();

        m_renderer->Render(m_app->GetCurrentScene()->GetMainCameraRef());
        //NY_DEBUG("FPS: {}", 1000000.0f / Time::Delta());
        //NY_DEBUG("Frame time: {}ms", Time::Delta() / 1000.f);
    }

    void Engine::Shutdown()
    {
        m_app->Shutdown();
        m_app.reset();

        m_renderer.reset();
        m_materialManager.reset();

        m_window->Close();
        m_window.reset();

        Log::Deinit();
    }
} // namespace ny::Core