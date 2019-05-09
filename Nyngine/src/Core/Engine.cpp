#include "pch.h"
#include "Engine.h"
#include "Application.h"
#include "ImGui/ImGuiSystem.h"

namespace ny::Core
{
    Engine* Engine::GetInstance()
    {
        static Engine instance;
        return &instance;
    }

    Application* Engine::GetApplication()
    {
        return GetInstance()->m_app;
    }

    void Engine::Run(Application* app)
    {
        NY_ASSERT(app, "Application ptr is null!!");
        m_app = app;

        Init();

        while (m_state == State::Running)
        {
            Tick();
        }

        Shutdown();
    }

    void Engine::Init()
    {
        Time::Init();
        Log::Init();

        m_window = std::make_unique<Window>();
        m_renderer = std::make_unique<Renderer>();
        m_renderer->Init();

        m_app->PreInit();
        m_app->Init();
        m_app->LateInit();

        m_state = State::Running;
    }

    void Engine::Tick()
    {
        NY_ASSERT(m_app, "");

        Time::Update();
        m_renderer->BeginFrame();
        ImGuiSystem::GetInstance()->Update();

        m_app->Tick();

        m_window->Update();

        //NY_DEBUG("FPS: {}", 1000000.0f / Time::Delta());
        //NY_DEBUG("Frame time: {}ms", Time::Delta() / 1000.f);
    }

    void Engine::Shutdown()
    {
        m_window->Close();
    }
} // namespace ny::Core