#pragma once
#include "Scene\Scene.h"

class MainScene : public ny::Scene
{
public:
    virtual void Init() override;
    virtual void Destroy() override;
    virtual void Update() override;
};
