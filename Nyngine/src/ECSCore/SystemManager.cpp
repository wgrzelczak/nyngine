#include "pch.h"
#include "SystemManager.h"
#include "Core\FieldDetection.h"

namespace ny::ECS::Core
{
    SystemManager::~SystemManager()
    {
        RemoveSystems();
    }

    void SystemManager::RegisterSystem(std::shared_ptr<SystemBase> sys, SystemTypeId id)
    {
        m_systems.insert_or_assign(id, sys);
    }

    void SystemManager::UnregisterSystem(SystemTypeId id)
    {
        m_systems.erase(id);
    }

    void SystemManager::UnregisterSystems()
    {
        m_systems.clear();
    }

    void SystemManager::RemoveSystem(SystemTypeId id)
    {
        UnregisterSystem(id);
    }

    void SystemManager::RemoveSystems()
    {
        UnregisterSystems();
    }

    void SystemManager::Update()
    {
        using Data = std::pair<SystemTypeId, std::shared_ptr<SystemBase>>;

        auto Update = [](Data element) {
            element.second->Update();
        };

        std::for_each(std::begin(m_systems), std::end(m_systems), Update);
    }
} // namespace ny::ECS::Core