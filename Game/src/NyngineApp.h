#pragma once
#include "Core\Application.h"
#include "Core\Engine.h"
#include "Core\EngineLayer.h"
#include "Core\Window.h"
#include <variant>

using namespace ny;
using namespace ny::Core;

class NyngineApp : public ny::Core::ApplicationExt<std::variant<EngineLayer>>
{
public:
    NyngineApp();
    virtual ~NyngineApp();
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Shutdown() override;
};
