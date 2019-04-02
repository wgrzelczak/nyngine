#pragma once
#include "Core\Event\InputEvents.h"
#include "Core\Event\WindowEvents.h"
#include "Preinclude.h"
#include "Scene\Scene.h"

class GameLayer
{
  public:
    GameLayer() { OnEnable(); }
    ~GameLayer() { OnDisable(); }

    void OnEnable();
    void OnDisable();
    void OnUpdate();

  private:
    ny::Scene m_scene;
};