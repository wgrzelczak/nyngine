#pragma once
#include "Preinclude.h"

namespace ny::Rendering
{
    class Renderer
    {
    public:
        void BeginFrame();
    };
} // namespace ny::Rendering

namespace ny
{
    using Renderer = ny::Rendering::Renderer;
}