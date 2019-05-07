#include "pch.h"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace ny::Rendering
{
    Camera::Camera()
    {
        UpdateView();
    }

    Camera::Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up) :
        m_position(position), m_front(forward), m_up(up)
    {
        UpdateView();
    }

    glm::mat4 Camera::View() const
    {
        return m_view;
    }

    glm::mat4 Camera::Projection() const
    {
        return m_projection;
    }

    void Camera::UpdateView()
    {
        m_view = glm::lookAt(m_position, m_position + m_front, m_up);
    }

    void Camera::SetPerspective(f32 fov, f32 aspect, f32 nearClip, f32 farClip)
    {
        m_projection = glm::perspective(fov, aspect, nearClip, farClip);
    }
    void Camera::SetOrtographic(f32 left, f32 right, f32 top, f32 bottom, f32 nearClip, f32 farClip)
    {
        m_projection = glm::ortho(left, right, top, bottom, nearClip, farClip);
    }

} // namespace ny::Rendering