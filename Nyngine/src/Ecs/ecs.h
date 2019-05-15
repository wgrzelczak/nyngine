#pragma once
#include "Component.h"
#include "ComponentManager.h"
#include "Entity.h"
#include "EventManager.h"
#include "Preinclude.h"
#include "SystemManager.h"

namespace engine
{
    using namespace ecs;

    class ECS final
    {
    public:
        static ECS* const Get()
        {
            static ECS mInstance;
            return &mInstance;
        }

        ComponentManager* const GetComponentManager()
        {
            return &mComponentManager;
        }

        SystemManager* const GetSystemManager()
        {
            return &mSystemManager;
        }

        EventManager* const GetEventManager()
        {
            return &mEventManager;
        }

    private:
        //todo disable all constructs and operators
        ECS() {}

        //move in to heap (?)
        ComponentManager mComponentManager;
        SystemManager mSystemManager;
        EventManager mEventManager;
    };
} // namespace engine