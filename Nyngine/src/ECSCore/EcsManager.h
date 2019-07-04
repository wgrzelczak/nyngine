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
        EcsManager() :
            m_componentManager(),
            m_systemManager(),
            m_eventManager()
        {
        }

        ComponentManager* GetComponentManager()
        {
            return &m_componentManager;
        }

        SystemManager* GetSystemManager()
        {
            return &m_systemManager;
        }

        EventManager* GetEventManager()
        {
            return &m_eventManager;
        }

    private:
        ComponentManager m_componentManager;
        SystemManager m_systemManager;
        EventManager m_eventManager;
    };
} // namespace ny::ECS::Core