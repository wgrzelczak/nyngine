#include "pch.h"
#include "Entity.h"

namespace ny::ECS::Core
{
    static u32 NEXT_ENTITY_ID = 0;

    Entity::Entity(std::weak_ptr<EcsManager> ecs) :
        m_ecs(ecs),
        m_id(NEXT_ENTITY_ID++)
    {
    }

    u32 Entity::GetId() const
    {
        return m_id;
    }
} // namespace ny::ECS::Core