#include "pch.h"
#include "MeshRendererSystem.h"
#include "Core\Engine.h"

namespace ny::ECS
{
    MeshRendererSystem::MeshRendererSystem()
    {
        m_updateCallback = [](const std::shared_ptr<MeshRendererComponent>& component) {
            ny::Rendering::Command cmd;
            cmd.m_material = component->m_model->GetMaterial();
            cmd.m_mesh = component->m_model->GetMesh();
            cmd.m_transform = component->m_model->GetModelMatrix();

            ny::IEngine->GetRenderer().PushCommand(std::move(cmd));
        };
    }
} // namespace ny::ECS