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
        void OnEarlyUpdate();
        void OnUpdate();
        void OnLateUpdate();
    };
} // namespace ny