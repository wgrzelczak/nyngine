#pragma once
#include "Preinclude.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace ny::Rendering
{
    class Camera
    {
    public:
        glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_rotation = {0.0f, 0.0f, 0.0f};

        glm::mat4 GetViewMatrix()
        {
            return glm::lookAt(m_position, m_position + m_front, m_up);
        }

    private:
        glm::vec3 m_front = {0.0f, 0.0f, -1.0f};
        glm::vec3 m_up = {0.0f, 1.0f, 0.0f};
        glm::vec3 m_right = {1.0f, 0.0f, 0.0f};
        glm::vec3 m_worldUp = {0.0f, 1.0f, 0.0f};
    };
} // namespace ny::Rendering