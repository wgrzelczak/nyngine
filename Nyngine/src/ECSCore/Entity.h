#pragma once
#include "Preinclude.h"

namespace ny::ECS::Core
{
    class EcsManager;
    class Entity
    {
    public:
        Entity(std::weak_ptr<EcsManager> ecs);
        u32 GetId() const;

        template <class T>
        std::shared_ptr<T> GetComponent() const;

        template <class T>
        std::shared_ptr<T> AddComponent() const;

    private:
        std::weak_ptr<EcsManager> m_ecs;
        const u32 m_id;
    };

    template <class T>
    inline std::shared_ptr<T> Entity::GetComponent() const
    {
        static_assert(std::is_base_of<ComponentBase, T>(), "Template param should derive from Component: " __FUNCSIG__);

        if (auto ecs = m_ecs.lock())
            return ecs->GetComponentManager()->GetEntityComponent<T>(this);
        NY_ERROR("ECS is nullptr!!");
        return std::shared_ptr<T>();
    }

    template <class T>
    inline std::shared_ptr<T> Entity::AddComponent() const
    {
        static_assert(std::is_base_of<ComponentBase, T>(), "Template param should derive from Component: " __FUNCSIG__);
        if (auto ecs = m_ecs.lock())
            return ecs->GetComponentManager()->AddEntityComponent<T>(this);
        NY_ERROR("ECS is nullptr!!");
        return std::shared_ptr<T>();
    }
} // namespace ny::ECS::Core