#pragma once
#include "Preinclude.h"
#include "glm/glm.hpp"

namespace ny::Rendering
{
    class LightDirectional
    {
    public:
        bool m_enabled = true;
        glm::vec3 m_position{0, 1, 0};
        glm::vec3 m_color{0.972, 0.913, 0.666};
        float m_ambientStrength{0.1f};
        float m_specularStrength{0.5f};
        i32 m_specularShininess{32};
    };
} // namespace ny::Rendering