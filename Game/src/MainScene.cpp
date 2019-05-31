#include "pch.h"
#include "MainScene.h"
#include "ECS\MeshRendererSystem.h"
void MainScene::Init()
{
    auto meshRendererSystem = Ecs::GetSystemManager()->RegisterSystem<ny::ECS::MeshRendererSystem>();

    m_box.AddComponent<ny::ECS::MeshRendererComponent>();
    meshRendererSystem->RegisterEntity(&m_box);
}

void MainScene::Destroy()
{
}

void MainScene::Update()
{
}
