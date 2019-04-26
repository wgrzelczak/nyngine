#pragma once
#include "Material.h"
#include "Preinclude.h"

namespace ny::Rendering
{
    class Renderer
    {
    public:
        void Init();
        void BeginFrame();

    private:
        std::shared_ptr<Material> m_material = nullptr;
    };
} // namespace ny::Rendering

namespace ny
{
    using Renderer = ny::Rendering::Renderer;
}