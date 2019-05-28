#pragma once
#include "Event/Event.h"
#include "FieldDetection.h"
#include "Window.h"
#include <variant>

namespace ny::Core
{
    class Application
    {
    public:
        void PreInit() {}
        virtual void Init() = 0;
        void LateInit() {}
        virtual void Tick() = 0;
        virtual void Shutdown() = 0;
    };
} // namespace ny::Core
