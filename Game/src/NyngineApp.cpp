#include "pch.h"
#include "NyngineApp.h"
#include "ECS\Ecs.h"

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
    m_currentScene->Update();
}

void NyngineApp::Shutdown()
{
    NY_TRACE("Shutting down...");
    m_currentScene->Destroy();
    delete m_currentScene;
}
