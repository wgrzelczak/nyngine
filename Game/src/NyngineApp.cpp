#include "pch.h"
#include "NyngineApp.h"

NyngineApp::NyngineApp()
{
}

NyngineApp::~NyngineApp()
{
}

void NyngineApp::PreInit()
{
}

void NyngineApp::Init()
{
    NY_TRACE("Initializing...");

    m_window = std::make_unique<Window>();

    PushLayer<EngineLayer>();
    PushLayer<ImGuiLayer>();

    NY_TRACE("Initialized");
}

void NyngineApp::Tick()
{
    UpdateLayers();

    m_window->Update();
}

void NyngineApp::Shutdown()
{
    NY_TRACE("Shutting down...");
    m_window->Close();
}
