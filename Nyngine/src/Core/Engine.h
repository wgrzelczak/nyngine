#pragma once
#include "Application.h"
#include "Event\InputEvents.h"
#include "Event\WindowEvents.h"
#include "FieldDetection.h"

namespace ny::Core
{
    class Engine
    {
    public:
        enum class State
        {
            Init,
            Running,
            ShuttingDown
        };

    public:
        static Engine* GetInstance();
        static Application* GetApplication();

    protected:
        Engine() {}

    public:
        Engine(Engine&) = delete;
        Engine(Engine&&) = delete;

        void Run(Application* app);

        void OnEvent(Event& e);

        void SetState(State state) { m_state = state; }

    private:
        void Init();
        void Tick();

        State m_state = State::Init;
        Application* m_app = nullptr;
    };

#define IEngine Core::Engine::GetInstance()

    inline void Engine::OnEvent(Event& e)
    {
        NY_ASSERT(m_app, "");
        m_app->OnEvent(e);
    }
} // namespace ny::Core
