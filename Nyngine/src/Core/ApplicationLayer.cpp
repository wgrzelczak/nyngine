#pragma once
#include "pch.h"
#include "ApplicationLayer.h"
#include "Application.h"

namespace ny::Core
{
    void ApplicationLayer::OnEnable()
    {
        m_scene.Init();
    }

    void ApplicationLayer::OnDisable()
    {
        m_scene.Destroy();
    }

    void ApplicationLayer::OnUpdate()
    {
        m_scene.Update();
    }

    void ApplicationLayer::OnEvent(Core::WindowClosedEvent e)
    {
        IApp->SetState(ApplicationState::ShuttingDown);
    }
} // namespace ny::Core