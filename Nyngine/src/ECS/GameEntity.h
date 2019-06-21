#pragma once
#include "ECSCore/Entity.h"
#include "Transform.h"

namespace ny::ECS
{
    class GameEntity : public Core::Entity
    {
    public:
        Transform m_transform;
    };
} // namespace ny::ECS