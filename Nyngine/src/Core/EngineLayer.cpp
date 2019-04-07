#pragma once
#include "pch.h"
#include "EngineLayer.h"
#include "Engine.h"

namespace ny::Core
{
    void EngineLayer::OnEnable()
    {
    }

    void EngineLayer::OnDisable()
    {
    }

    void EngineLayer::OnUpdate()
    {
    }

    void EngineLayer::OnEvent(Core::WindowClosedEvent e)
    {
        Engine::GetInstance()->SetState(Engine::State::ShuttingDown);
    }
} // namespace ny::Core