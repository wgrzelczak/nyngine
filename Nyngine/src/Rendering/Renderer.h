#pragma once
#include "Preinclude.h"
#include "Camera.h"
#include "CommandBuffer.h"
#include "LightDirectional.h"

namespace ny::Rendering
{
    class Renderer
    {
    public:
        Renderer();

        void Init();
        void Render();

        void PushCommand(Command&& cmd);

    private:
        Camera m_camera;
        LightDirectional m_directionalLight;

        std::unique_ptr<CommandBuffer> m_commandBuffer = nullptr;

        void RegisterImGuiDebug();
    };
} // namespace ny::Rendering

namespace ny
{
    using Renderer = ny::Rendering::Renderer;
}