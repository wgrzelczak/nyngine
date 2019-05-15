#pragma once
#include "Preinclude.h"
#include "System.h"
#include <list>
#include <memory>

namespace ny::Ecs
{
    class SystemManager
    {
    public:
        ~SystemManager();

        template <class T>
        std::shared_ptr<T> CreateSystem();
        void RemoveSystem(const std::weak_ptr<SystemBase>& sys);
        void RemoveSystems();
        void Update();

    private:
        void RegisterSystem(const std::shared_ptr<SystemBase>& sys);
        void UnregisterSystem(const std::shared_ptr<SystemBase>& sys);
        void UnregisterSystems();

        std::list<std::shared_ptr<SystemBase>> m_systems;
    };

    template <class T>
    inline std::shared_ptr<T> SystemManager::CreateSystem()
    {
        static_assert(std::is_base_of<SystemBase, T>(), "Template param should derive from System: " __FUNCSIG__);
        std::shared_ptr<T> sys(new T());
        RegisterSystem(sys);
        return sys;
    }
} // namespace ny::Ecs