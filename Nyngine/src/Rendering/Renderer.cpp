#include "pch.h"
#include "Renderer.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    void Renderer::BeginFrame()
    {
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
} // namespace ny::Rendering