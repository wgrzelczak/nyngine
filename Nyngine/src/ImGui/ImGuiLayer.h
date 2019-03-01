#pragma once
#include "Core\Event\InputEvents.h"
#include "Core\Event\WindowEvents.h"
#include "Preinclude.h"

namespace ny
{
    class ImGuiLayer
    {
      public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnEnable();
        void OnDisable();
        void OnUpdate();

        void OnEvent(Core::WindowResizedEvent e);
        void OnEvent(Core::KeyPressedEvent e);
        void OnEvent(Core::KeyReleasedEvent e);
        void OnEvent(Core::KeyTypedEvent e);
        void OnEvent(Core::MouseButtonPressedEvent e);
        void OnEvent(Core::MouseButtonReleasedEvent e);
        void OnEvent(Core::MouseMovedEvent e);
        void OnEvent(Core::MouseScrolledEvent e);

      private:
        f32 m_time;
    };
} // namespace ny