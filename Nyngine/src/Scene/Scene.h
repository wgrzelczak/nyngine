#pragma once
#include "ECS\Ecs.h"
#include "ImGui\ImGuiSystem.h"
#include "Rendering\Camera.h"

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

        Camera& GetMainCameraRef() { return m_mainCamera; }

    protected:
        Camera m_mainCamera;
    };
} // namespace ny