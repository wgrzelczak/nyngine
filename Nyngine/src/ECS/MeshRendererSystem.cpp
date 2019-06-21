#include "pch.h"
#include "MeshRendererSystem.h"
#include "Core\Engine.h"

namespace ny::ECS
{
    MeshRendererSystem::MeshRendererSystem()
    {
        m_updateCallback = [](const std::shared_ptr<MeshRendererComponent>& component) {
            ny::Rendering::Command cmd;
            cmd.m_material = component->m_material;
            cmd.m_mesh = component->m_mesh;
            cmd.m_transform = component->CalculateModelMatrix();

            ny::IEngine->GetRenderer().PushCommand(std::move(cmd));
        };
    }
} // namespace ny::ECS