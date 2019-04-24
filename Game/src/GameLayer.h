#pragma once
#include "Core\Event\InputEvents.h"
#include "Core\Event\WindowEvents.h"
#include "Core\Layer.h"
#include "Preinclude.h"
#include "Scene\Scene.h"

class GameLayer : public ny::Core::Layer
{
public:
    void OnEnable();
    void OnDisable();
    void OnUpdate();

private:
    ny::Scene m_scene;
};