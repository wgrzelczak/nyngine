#pragma once
#include "Component.h"
#include "Preinclude.h"
#include <memory>
#include <type_traits>

namespace engine::ecs::core
{
    class Entity
    {
    public:
        Entity();
        ~Entity();

        id::Entity GetId() const
        {
            return mId;
        }

        template <class T>
        std::weak_ptr<T> GetComponent() const;

        template <class T>
        std::weak_ptr<T> AddComponent() const;

    private:
        static id::Entity NEXT_ID;
        const id::Entity mId;
    };

    template <class T>
    inline std::weak_ptr<T> Entity::GetComponent() const
    {
        static_assert(std::is_base_of<ComponentBase, T>(), "Template param should derive from Component: " __FUNCSIG__);
        return ECS::Get()->GetComponentManager()->GetEntityComponent<T>(mId);
    }

    template <class T>
    inline std::weak_ptr<T> Entity::AddComponent() const
    {
        static_assert(std::is_base_of<ComponentBase, T>(), "Template param should derive from Component: " __FUNCSIG__);
        return ECS::Get()->GetComponentManager()->AddEntityComponent<T>(mId);
    }
} // namespace engine::ecs::core