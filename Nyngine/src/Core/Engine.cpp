#include "pch.h"
#include "Engine.h"
#include "Application.h"
#include "glad\glad.h"

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
    }

    void Engine::Init()
    {
        Time::Init();
        Log::Init();

        m_app->PreInit();
        m_app->Init();

        m_state = State::Running;
    }

    void Engine::Tick()
    {
        NY_ASSERT(m_app, "");

        Time::Update();

        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_app->Tick();

        NY_DEBUG("FPS: {}", 1000000.0f / Time::Delta());
    }
} // namespace ny::Core