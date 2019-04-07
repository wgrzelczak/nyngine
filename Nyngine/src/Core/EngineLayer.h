#pragma once
#include "Core\Event\InputEvents.h"
#include "Core\Event\WindowEvents.h"
#include "Preinclude.h"

namespace ny::Core
{
    class EngineLayer
    {
      public:
        EngineLayer() { OnEnable(); }
        ~EngineLayer() { OnDisable(); }

        void OnEnable();
        void OnDisable();
        void OnUpdate();

        void OnEvent(Core::WindowClosedEvent e);
    };
} // namespace ny::Core