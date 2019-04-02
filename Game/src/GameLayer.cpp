#pragma once
#include "pch.h"
#include "GameLayer.h"

void GameLayer::OnEnable()
{
    m_scene.Init();
}

void GameLayer::OnDisable()
{
    m_scene.Destroy();
}

void GameLayer::OnUpdate()
{
    m_scene.Update();
}