#pragma once
#include "Preinclude.h"
#include "Shader.h"

namespace ny::Rendering
{
    class Renderer
    {
    public:
        void Init();
        void BeginFrame();

    private:
        u32 m_programId;
        std::vector<std::shared_ptr<Shader>> m_shaders;
    };
} // namespace ny::Rendering

namespace ny
{
    using Renderer = ny::Rendering::Renderer;
}