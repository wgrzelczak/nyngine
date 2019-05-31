#pragma once
#include "ECSCore\Ecs.h"
#include "ImGui\ImGuiSystem.h"

namespace ny
{
    class Scene
    {
    public:
        virtual void Init() = 0;
        virtual void Destroy() = 0;
        virtual void Update() = 0;
    };
} // namespace ny