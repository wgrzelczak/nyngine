#pragma once
#include "Entity.h"
#include "Preinclude.h"

namespace engine::ecs::core
{
    class SystemBase
    {
    public:
        Priority mPriority;
        virtual void Update() = 0;
        virtual void RegisterEntity(Entity* const entity) = 0;
    };
} // namespace engine::ecs::core