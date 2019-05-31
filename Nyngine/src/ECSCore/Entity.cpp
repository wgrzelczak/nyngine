#include "pch.h"
#include "Entity.h"

namespace ny::ECS::Core
{
    static u32 NEXT_ENTITY_ID = 0;

    Entity::Entity() :
        m_id(NEXT_ENTITY_ID++)
    {
    }
    inline u32 Entity::GetId() const
    {
        return m_id;
    }
} // namespace ny::ECS::Core