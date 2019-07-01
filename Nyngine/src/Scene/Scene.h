#pragma once
#include "ECS\Ecs.h"
#include "ImGui\ImGuiSystem.h"

namespace ny
{
    class Scene
    {
    public:
        virtual void Init() = 0;
        virtual void Destroy() = 0;
        virtual void Update() = 0;

        std::vector<std::shared_ptr<EcsEntity>> m_objects;
        EcsPtr m_ecs{nullptr};
    };
} // namespace ny