#pragma once
#include "ComponentManager.h"
#include "Entity.h"
#include "EventManager.h"
#include "SystemManager.h"

namespace ny::ECS::Core
{
    class EcsManager final
    {
    public:
        static EcsManager* const Get()
        {
            static EcsManager instance;
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
        EcsManager() {}

        ComponentManager m_componentManager;
        SystemManager m_systemManager;
        EventManager m_eventManager;
    };
} // namespace ny::ECS::Core