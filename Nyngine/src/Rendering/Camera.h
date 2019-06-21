#pragma once
#include "Preinclude.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace ny::Rendering
{
    class Camera
    {
    public:
        Camera();
        Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up);

        glm::mat4 View() const;
        glm::mat4 Projection() const;

        void UpdateView();

        void SetPerspective(f32 fov, f32 aspect, f32 nearClip, f32 farClip);
        void SetOrtographic(f32 left, f32 right, f32 top, f32 bottom, f32 nearClip, f32 farClip);

        glm::vec3 GetPosition() const { return m_position; }
        glm::vec3& GetPositionRef();

    private:
        glm::vec3 m_front = {0.0f, 0.0f, -1.0f};
        glm::vec3 m_up = {0.0f, 1.0f, 0.0f};
        glm::vec3 m_right = {1.0f, 0.0f, 0.0f};
        glm::vec3 m_worldUp = {0.0f, 1.0f, 0.0f};

        glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_rotation = {0.0f, 0.0f, 0.0f};
        glm::mat4 m_projection = glm::mat4();
        glm::mat4 m_view = glm::mat4();
    };
} // namespace ny::Rendering