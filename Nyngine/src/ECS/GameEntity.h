#pragma once
#include "ECSCore/Entity.h"
#include "ImGui/ImGuiSystem.h"
#include "Transform.h"

namespace ny::ECS
{
    namespace Core
    {
        class EcsManager;
    }

    class GameEntity : public Core::Entity
    {
    public:
        GameEntity(std::weak_ptr<Core::EcsManager> ecs) :
            Core::Entity(ecs) {}

        std::string m_name{"Id#" + std::to_string(GetId())};
        Transform m_transform;

        void SetParent(std::shared_ptr<GameEntity> parent)
        {
            m_parent = parent;
            if (m_parent)
                m_transform.SetParent(&parent->m_transform);
        }

        std::shared_ptr<GameEntity> GetParent() const { return m_parent; }

        void AddChild(std::shared_ptr<GameEntity> child)
        {
            m_children.push_back(child);
        }

    private:
        std::shared_ptr<GameEntity> m_parent{nullptr};
        std::vector<std::shared_ptr<GameEntity>> m_children;

    public:
        void ImGuiDraw()
        {
            if (ImGui::TreeNode(m_name.c_str()))
            {
                ImGui::DragFloat3(std::string("Position##" + std::to_string(GetId())).c_str(), &m_transform.GetPositionRef().x, 0.01f);
                ImGui::DragFloat4(std::string("Rotation##" + std::to_string(GetId())).c_str(), &m_transform.GetRotationRef().x, 0.01f);
                ImGui::DragFloat3(std::string("Scale##" + std::to_string(GetId())).c_str(), &m_transform.GetScaleRef().x, 0.01f);

                m_transform.NormalizeRotation();

                for (const auto& c : m_children)
                {
                    c->ImGuiDraw();
                }

                ImGui::TreePop();
            }
        }
    };
} // namespace ny::ECS