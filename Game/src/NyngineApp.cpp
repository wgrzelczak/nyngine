#include "pch.h"
#include "NyngineApp.h"

NyngineApp::NyngineApp()
{
}

NyngineApp::~NyngineApp()
{
}

void NyngineApp::Init()
{
    NY_TRACE("Initializing...");

    PushLayer<EngineLayer>();
    PushLayer<ImGuiLayer>();

    EnableLayer<EngineLayer>();
    EnableLayer<ImGuiLayer>();

    NY_TRACE("Initialized");
}

void NyngineApp::Tick()
{
    UpdateLayers();
}

void NyngineApp::Shutdown()
{
    NY_TRACE("Shutting down...");
}
