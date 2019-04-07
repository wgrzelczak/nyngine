#pragma once
#include "Core\Application.h"
#include "Core\EngineLayer.h"
#include "Core\Window.h"
#include "ImGui\ImGuiLayer.h"
#include <variant>

using namespace ny;
using namespace ny::Core;

class NyngineApp : public ny::Core::ApplicationExt<std::variant<EngineLayer, ImGuiLayer>>
{
  public:
    NyngineApp();
    virtual ~NyngineApp();
    virtual void PreInit() override;
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Shutdown() override;

    Window& GetWindow() const override { return *m_window; }

  private:
    std::unique_ptr<Window> m_window = nullptr;
};
