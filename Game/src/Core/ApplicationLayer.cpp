#pragma once
#include "pch.h"
#include "ApplicationLayer.h"
#include "Application.h"

namespace ny::Core
{
    void ApplicationLayer::OnEvent(Core::WindowClosedEvent e)
    {
        IApp->SetState(ApplicationState::ShuttingDown);
    }
} // namespace ny::Core