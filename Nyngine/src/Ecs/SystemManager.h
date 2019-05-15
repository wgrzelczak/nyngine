#pragma once
#include "Preinclude.h"
#include "SystemBase.h"
#include <list>
#include <memory>

namespace engine::ecs
{
    class SystemManager
    {
    public:
        SystemManager();
        ~SystemManager();

        template <class T>
        std::weak_ptr<T> CreateSystem();
        void RemoveSystem(const std::weak_ptr<core::SystemBase>& sys);
        void RemoveSystems();
        void Update();

    private:
        void RegisterSystem(const std::shared_ptr<core::SystemBase>& sys);
        void UnregisterSystem(const std::shared_ptr<core::SystemBase>& sys);
        void UnregisterSystems();

        std::list<std::shared_ptr<core::SystemBase>> mSystems;
    };

#include "SystemManager.inl"
} // namespace engine::ecs