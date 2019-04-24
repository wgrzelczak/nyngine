#pragma once
#include "Core\Event\InputEvents.h"
#include "Core\Event\WindowEvents.h"
#include "Layer.h"
#include "Preinclude.h"

namespace ny::Core
{
    class EngineLayer : public Layer
    {
    public:
        void OnEnable();
        void OnDisable();
        void OnUpdate();

        void OnEvent(Core::WindowClosedEvent e);
        void OnEvent(Core::KeyPressedEvent e);
    };
} // namespace ny::Core