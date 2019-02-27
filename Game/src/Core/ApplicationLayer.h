#pragma once
#include "Core\Event\InputEvents.h"
#include "Core\Event\WindowEvents.h"
#include "Preinclude.h"

namespace ny::Core
{
    class ApplicationLayer
    {
      public:
        ApplicationLayer() {}
        ~ApplicationLayer() {}

        void OnEnable() {}
        void OnDisable() {}
        void OnUpdate() {}

        void OnEvent(Core::WindowClosedEvent e);
    };
} // namespace ny::Core