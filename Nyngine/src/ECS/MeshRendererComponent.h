#pragma once
#include "ECSCore\Ecs.h"
#include "Rendering\Model.h"

namespace ny::ECS
{
    class MeshRendererComponent : public EcsComponent<MeshRendererComponent>
    {
    public:
        std::shared_ptr<ny::Rendering::Model> m_model;
    };
} // namespace ny::ECS