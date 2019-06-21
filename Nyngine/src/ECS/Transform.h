#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace ny::ECS
{
    class Transform
    {
    public:
        Transform() {}
        void SetPosition(const glm::vec3& position) { m_position = position; }
        void SetRotation(const glm::quat& rotation) { m_rotation = rotation; }
        void SetScale(const glm::vec3& scale) { m_scale = scale; }

        glm::mat4 CalculateModelMatrix() const;

        void NormalizeRotation() { m_rotation = glm::normalize(m_rotation); }
        void AddRotation(const glm::quat& rotation);
        glm::quat& GetRotationRef() { return m_rotation; }

    private:
        glm::vec3 m_position{0.0f, 0.0f, 0.0f};
        glm::quat m_rotation{0.0f, 0.0f, 0.0f, 1.0f};
        glm::vec3 m_scale{0.0f, 0.0f, 0.0f};
    };
} // namespace ny::ECS