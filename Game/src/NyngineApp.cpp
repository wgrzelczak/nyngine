#include "pch.h"
#include "NyngineApp.h"
#include "ECSCore\ecs.h"

NyngineApp::NyngineApp()
{
}

NyngineApp::~NyngineApp()
{
}

void NyngineApp::Init()
{
    NY_TRACE("Initializing...");

    NY_TRACE("Initialized");
}

void NyngineApp::Tick()
{
    Ecs::Get()->GetSystemManager()->Update();
}

void NyngineApp::Shutdown()
{
    NY_TRACE("Shutting down...");
}
