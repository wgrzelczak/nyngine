#pragma once
#include "Preinclude.h"
#include "ECS\Ecs.h"
#include "Rendering\Material.h"
#include "Rendering\Mesh.h"
#include "Transform.h"

using namespace ny::Rendering;

namespace ny::ECS
{
    class MeshRendererComponent : public EcsComponent<MeshRendererComponent>
    {
    public:
        MeshRendererComponent(const EcsCoreEntity* e) :
            EcsComponent<MeshRendererComponent>(e) {}

        glm::mat4 CalculateModelMatrix() const
        {
            GameEntity* entity = (GameEntity*)GetEntity();
            return entity->m_transform.CalculateModelMatrix();
        }

        Material* m_material{nullptr};
        Mesh* m_mesh{nullptr};
    };
} // namespace ny::ECS