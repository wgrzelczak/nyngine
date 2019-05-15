#pragma once
#include "Preinclude.h"

namespace engine::ecs::core
{
    class ComponentBase
    {
    public:
        ComponentBase() :
            isEnabled(true)
        {
        }
        bool isEnabled;
    };

    static id::Component NEXT_ID = 0;
} // namespace engine::ecs::core