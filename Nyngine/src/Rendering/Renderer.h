#pragma once
#include "Camera.h"
#include "CommandBuffer.h"
#include "Model.h"
#include "Preinclude.h"
namespace ny::Rendering
{
    class Renderer
    {
    public:
        Renderer();

        void Init();
        void Render();

    private:
        Camera m_camera;
        std::shared_ptr<Material> m_material = nullptr;
        std::unique_ptr<CommandBuffer> m_commandBuffer = nullptr;

        Model* tmp_model = nullptr;
        Mesh* tmp_mesh = nullptr;

        void RegisterImGuiDebug();
    };
} // namespace ny::Rendering

namespace ny
{
    using Renderer = ny::Rendering::Renderer;
}