#include "Entity.h"

namespace engine::ecs::core
{
    id::Entity Entity::NEXT_ID = 0;

    Entity::Entity() :
        mId(NEXT_ID++)
    {
    }

    Entity::~Entity()
    {
    }
} // namespace engine::ecs::core