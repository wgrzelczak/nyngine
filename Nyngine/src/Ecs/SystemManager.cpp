#include "SystemManager.h"
#include <algorithm>

namespace engine::ecs
{
    SystemManager::SystemManager()
    {
    }

    SystemManager::~SystemManager()
    {
        RemoveSystems();
    }

    void SystemManager::RegisterSystem(const std::shared_ptr<core::SystemBase>& sys)
    {
        const auto desiredPriority = sys->mPriority;
        auto comp = [&desiredPriority](const std::shared_ptr<core::SystemBase>& lhs) {
            return lhs->mPriority >= desiredPriority;
        };

        if (auto crIt = std::find_if(std::crbegin(mSystems), std::crend(mSystems), comp); crIt != std::crend(mSystems))
        {
            mSystems.insert(crIt.base(), sys);
        }
        else
        {
            mSystems.push_front(sys);
        }
    }

    void SystemManager::UnregisterSystem(const std::shared_ptr<core::SystemBase>& sys)
    {
        mSystems.remove(sys);
    }

    void SystemManager::UnregisterSystems()
    {
        //todo check leaks
        mSystems.clear();
    }

    void SystemManager::RemoveSystem(const std::weak_ptr<core::SystemBase>& sys)
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
        std::for_each(std::begin(mSystems), std::end(mSystems), [](std::shared_ptr<core::SystemBase> sys) { sys->Update(); });
    }
} // namespace engine::ecs