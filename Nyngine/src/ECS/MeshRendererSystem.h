#pragma once
#include "ECSCore\Ecs.h"
#include "MeshRendererComponent.h"

namespace ny::ECS
{
    class MeshRendererSystem : public EcsSystem<MeshRendererComponent>
    {
    public:
        MeshRendererSystem()
        {
            m_updateCallback = [](const std::shared_ptr<MeshRendererComponent>& weak) {
                NY_DEBUG("update");
            };
        }
    };
} // namespace ny::ECS