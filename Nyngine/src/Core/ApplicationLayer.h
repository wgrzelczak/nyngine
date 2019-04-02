#pragma once
#include "Core\Event\InputEvents.h"
#include "Core\Event\WindowEvents.h"
#include "Preinclude.h"
#include "Scene\Scene.h"

namespace ny::Core
{
    class ApplicationLayer
    {
      public:
        ApplicationLayer() { OnEnable(); }
        ~ApplicationLayer() { OnDisable(); }

        void OnEnable();
        void OnDisable();
        void OnUpdate();

        void OnEvent(Core::WindowClosedEvent e);

      private:
        Scene m_scene;
    };
} // namespace ny::Core