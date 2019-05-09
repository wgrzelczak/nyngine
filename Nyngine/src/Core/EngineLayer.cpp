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
        //avoid disabling layer
        SetIsEnabled(true);
    }

    void EngineLayer::OnUpdate()
    {
    }

    void EngineLayer::OnEvent(Core::WindowClosedEvent e)
    {
        Engine::GetInstance()->SetState(Engine::State::ShuttingDown);
    }

    void EngineLayer::OnEvent(Core::KeyPressedEvent e)
    {
        if (e.keyCode == NY_KEY_F8)
        {
            //Engine::GetEngine()->ToggleDebugLayer();
        }
    }
} // namespace ny::Core