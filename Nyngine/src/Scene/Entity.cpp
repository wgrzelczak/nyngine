#include "pch.h"
#include "Entity.h"

namespace ny
{
    u32 Entity::lastId = 0;

    Entity::Entity() :
        m_id(lastId++)
    {}

    Entity::~Entity() {}

    void Entity::Destroy()
    {
        m_components.clear();
    }

} // namespace ny