#pragma once
#include "Entity.h"

namespace ny
{
    class Scene
    {
    public:
        Scene() {}
        ~Scene() {}

        void Init();
        void Destroy();
        void Update();

        std::vector<Entity> m_entities;
    };
} // namespace ny