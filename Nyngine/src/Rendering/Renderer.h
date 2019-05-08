#pragma once
#include "Camera.h"
#include "Material.h"
#include "Model.h"
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

        Model* tmp_model = nullptr;
        Mesh* tmp_mesh = nullptr;
    };
} // namespace ny::Rendering

namespace ny
{
    using Renderer = ny::Rendering::Renderer;
}