#pragma once
#include "Entity.h"

namespace ny::ECS::Core
{
    class ComponentBase
    {
    public:
        ComponentBase() :
            m_enabled(true)
        {}

        bool m_enabled;
    };

    template <class T>
    class Component : public ComponentBase
    {
    public:
        Component(const Entity* entity) :
            m_entity(entity) {}

        static u32 GetId() { return Id; }

        u32 GetEntityId() const
        {
            NY_ASSERT(m_entity, "Error! Entity not found");
            return m_entity->GetId();
        }

        const Entity* GetEntity() const
        {
            NY_ASSERT(m_entity, "Error! Entity not found");
            return m_entity;
        }

    private:
        const static u32 Id;
        const Entity* m_entity;
    };

    static u32 NEXT_COMPONENT_ID = 0;
    template <class T>
    const u32 Component<T>::Id = NEXT_COMPONENT_ID++;
} // namespace ny::ECS::Core