#pragma once
#include "Preinclude.h"
#include "Component.h"

namespace ny::ECS::Core
{
    class Entity
    {
    public:
        Entity();
        u32 GetId() const;

        template <class T>
        std::shared_ptr<T> GetComponent() const;

        template <class T>
        std::shared_ptr<T> AddComponent() const;

    private:
        const u32 m_id;
    };

    template <class T>
    inline std::shared_ptr<T> Entity::GetComponent() const
    {
        static_assert(std::is_base_of<ComponentBase, T>(), "Template param should derive from Component: " __FUNCSIG__);
        return ECS::GetComponentManager()->GetEntityComponent<T>(mId);
    }

    template <class T>
    inline std::shared_ptr<T> Entity::AddComponent() const
    {
        static_assert(std::is_base_of<ComponentBase, T>(), "Template param should derive from Component: " __FUNCSIG__);
        return ECS::GetComponentManager()->AddEntityComponent<T>(mId);
    }
} // namespace ny::ECS::Core