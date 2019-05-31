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

    m_currentScene = new MainScene();
    m_currentScene->Init();

    NY_TRACE("Initialized");
}

void NyngineApp::Tick()
{
    Ecs::Get()->GetSystemManager()->Update();
}

void NyngineApp::Shutdown()
{
    NY_TRACE("Shutting down...");
    delete m_currentScene;
}
