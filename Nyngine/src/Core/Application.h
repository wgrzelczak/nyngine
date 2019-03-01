#pragma once
#include "ApplicationLayer.h"
#include "FieldDetection.h"
#include "ImGui\ImGuiLayer.h"
#include "Preinclude.h"
#include "Window.h"
#include <variant>

namespace ny::Core
{
    enum class ApplicationState
    {
        Init,
        Running,
        ShuttingDown
    };

    using v_Layer = std::variant<ApplicationLayer, ImGuiLayer>;

    class Application
    {
      public:
        static Application* GetInstance();

      private:
        static Application* m_instance;

      public:
        Application();
        virtual ~Application();
        void Exec();

        template <class EventType>
        void OnEvent(EventType&& event);

        void SetState(ApplicationState state) { m_state = state; }
        Window& GetWindow() const { return *m_window; }

      private:
        void PreInit();
        void Init();
        void Run();
        void Shutdown();

        ApplicationState m_state;
        std::unique_ptr<Window> m_window = nullptr;
        std::vector<v_Layer> m_layers;
    };

#define IApp Core::Application::GetInstance()

    template <class EventType>
    inline void Application::OnEvent(EventType&& e)
    {
        auto dispatchEvent = [&](auto&& arg) {
            using LayerType = std::decay_t<decltype(arg)>;
            if constexpr (HasEvent<LayerType, EventType>)
            {
                arg.OnEvent(std::forward<EventType>(e));
            }
        };

        for (auto& l : m_layers)
        {
            if (!e.m_handled)
            {
                std::visit(dispatchEvent, l);
            }
        }
    }
} // namespace ny::Core
