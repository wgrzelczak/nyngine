#pragma once
#include "Core\Event\InputEvents.h"
#include "Core\Event\WindowEvents.h"
#include "Core\Layer.h"
#include "Preinclude.h"

namespace ny
{
    class ImGuiLayer : public ny::Core::Layer
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