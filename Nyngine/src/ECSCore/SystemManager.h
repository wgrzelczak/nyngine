#pragma once
#include "System.h"

namespace ny::ECS::Core
{
    class EcsManager;

    class SystemManager
    {
    public:
        SystemManager()
        {
        }

        ~SystemManager();

        template <class T>
        std::shared_ptr<T> CreateSystem();

        template <class T>
        std::shared_ptr<T> GetSystem(bool createIfNotFound = true);

        template <class T>
        void RemoveSystem();

        void RemoveSystems();
        void Update();

    private:
        void RegisterSystem(std::shared_ptr<SystemBase> sys, SystemTypeId id);
        void RemoveSystem(SystemTypeId id);
        void UnregisterSystem(SystemTypeId id);
        void UnregisterSystems();

        std::map<SystemTypeId, std::shared_ptr<SystemBase>> m_systems;
    };

    template <class T>
    inline std::shared_ptr<T> SystemManager::CreateSystem()
    {
        static_assert(std::is_base_of<SystemBase, T>(), "Template param should derive from System: " __FUNCSIG__);
        std::shared_ptr<T> sys(new T());
        RegisterSystem(std::static_pointer_cast<SystemBase>(sys), SystemType<T>::GetId());
        return sys;
    }

    template <class T>
    inline std::shared_ptr<T> SystemManager::GetSystem(bool createIfNotFound)
    {
        static_assert(std::is_base_of<SystemBase, T>(), "Template param should derive from System: " __FUNCSIG__);

        SystemTypeId systemId = SystemType<T>::GetId();

        if (auto it = m_systems.find(systemId); it != std::end(m_systems))
        {
            return std::static_pointer_cast<T>(m_systems.at(systemId));
        }

        return createIfNotFound ? CreateSystem<T>() : nullptr;
    }
    template <class T>
    inline void SystemManager::RemoveSystem()
    {
        static_assert(std::is_base_of<SystemBase, T>(), "Template param should derive from System: " __FUNCSIG__);

        RemoveSystem(SystemBase<T>::GetId());
    }
} // namespace ny::ECS::Core