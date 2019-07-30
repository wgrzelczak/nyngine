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
        void Init();
        void Render(const Camera& camera);

        void PushCommand(Command&& cmd);

    private:
        LightDirectional m_directionalLight;

        std::unique_ptr<CommandBuffer> m_commandBuffer{nullptr};

        void RegisterImGuiDebug();
    };
} // namespace ny::Rendering

namespace ny
{
    using Renderer = ny::Rendering::Renderer;
}