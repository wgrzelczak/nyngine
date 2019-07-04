#pragma once
#include "ECS\Ecs.h"
#include "MeshRendererComponent.h"

namespace ny::ECS
{
    class MeshRendererSystem : public EcsSystem<MeshRendererSystem, MeshRendererComponent>
    {
    public:
        MeshRendererSystem();
    };
} // namespace ny::ECS