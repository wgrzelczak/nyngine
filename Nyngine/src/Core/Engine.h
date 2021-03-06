#pragma once
#include "Application.h"
#include "Event\InputEvents.h"
#include "Event\WindowEvents.h"
#include "FieldDetection.h"
#include "Rendering/Renderer.h"

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

    protected:
        Engine() {}

    public:
        Engine(Engine&) = delete;
        Engine(Engine&&) = delete;

        i32 Run(Application* app);

        void Invoke(Event& e);
        void OnEvent(WindowClosedEvent& e);

        std::shared_ptr<Log> GetLogger() const { return m_logger; }

        void SetState(State state) { m_state = state; }
        Window& GetWindow() const { return *m_window; }
        Renderer& GetRenderer() const { return *m_renderer; }

    private:
        void Init();
        void Tick();
        void Shutdown();

        State m_state{State::Init};
        std::unique_ptr<Application> m_app{nullptr};
        std::shared_ptr<Log> m_logger{nullptr};

        std::unique_ptr<Renderer> m_renderer{nullptr};
        std::unique_ptr<Window> m_window{nullptr};
    };
} // namespace ny::Core

namespace ny
{
    using Engine = Core::Engine;
}