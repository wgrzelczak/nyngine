#pragma once
#include "Preinclude.h"
#include "ECS/Transform.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace ny::Rendering
{
    class Camera : public ECS::Transform
    {
    public:
        Camera();
        Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up);

        glm::mat4 View() const;
        glm::mat4 Projection() const;

        void UpdateView();

        void SetPerspective(f32 fov, f32 aspect, f32 nearClip, f32 farClip);
        void SetOrtographic(f32 left, f32 right, f32 top, f32 bottom, f32 nearClip, f32 farClip);

        glm::vec3& GetFrontRef() { return m_front; }

    private:
        glm::vec3 m_front{0.0f, 0.0f, -1.0f};
        glm::vec3 m_up{0.0f, 1.0f, 0.0f};
        glm::vec3 m_right{1.0f, 0.0f, 0.0f};
        glm::vec3 m_worldUp{0.0f, 1.0f, 0.0f};

        glm::mat4 m_projection{};
        glm::mat4 m_view{};
    };
} // namespace ny::Rendering

namespace ny
{
    using Camera = ny::Rendering::Camera;
}