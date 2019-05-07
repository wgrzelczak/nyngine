#pragma once
#include "Camera.h"
#include "Material.h"
#include "Preinclude.h"
namespace ny::Rendering
{
    class Renderer
    {
    public:
        Renderer();

        void Init();
        void BeginFrame();

    private:
        Camera m_camera;
        std::shared_ptr<Material> m_material = nullptr;
    };
} // namespace ny::Rendering

namespace ny
{
    using Renderer = ny::Rendering::Renderer;
}