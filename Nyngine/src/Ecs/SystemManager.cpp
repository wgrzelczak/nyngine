#include "pch.h"
#include "SystemManager.h"
#include "Core\FieldDetection.h"

namespace ny::Ecs
{
    SystemManager::~SystemManager()
    {
        RemoveSystems();
    }

    void SystemManager::RegisterSystem(const std::shared_ptr<SystemBase>& sys)
    {
        m_systems.push_front(sys);
    }

    void SystemManager::UnregisterSystem(const std::shared_ptr<SystemBase>& sys)
    {
        m_systems.remove(sys);
    }

    void SystemManager::UnregisterSystems()
    {
        //todo check leaks
        m_systems.clear();
    }

    void SystemManager::RemoveSystem(const std::weak_ptr<SystemBase>& sys)
    {
        if (auto shared = sys.lock())
        {
            UnregisterSystem(shared);
        }
    }

    void SystemManager::RemoveSystems()
    {
        UnregisterSystems();
    }

    void SystemManager::Update()
    {
        auto Update = [](std::shared_ptr<SystemBase> sys) {
            //if constexpr(HasUpdate)
            //sys->OnUpdate();
            sys->Update();
        };

        std::for_each(std::begin(m_systems), std::end(m_systems), Update);
    }
} // namespace ny::Ecs