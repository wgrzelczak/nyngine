#pragma once
#include "Component.h"
#include "ComponentManager.h"
#include "Entity.h"
#include "EventManager.h"
#include "Preinclude.h"
#include "SystemManager.h"

namespace ny::Ecs
{
    class Ecs final
    {
    public:
        static Ecs* const Get()
        {
            static Ecs instance;
            return &instance;
        }

        static ComponentManager* GetComponentManager()
        {
            return &Get()->m_componentManager;
        }

        static SystemManager* GetSystemManager()
        {
            return &Get()->m_systemManager;
        }

        static EventManager* GetEventManager()
        {
            return &Get()->m_eventManager;
        }

    private:
        Ecs() {}

        ComponentManager m_componentManager;
        SystemManager m_systemManager;
        EventManager m_eventManager;
    };
} // namespace ny::Ecs

using ECS = ny::Ecs::Ecs;