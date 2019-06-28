#include "pch.h"
#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

namespace ny::ECS
{
    void Transform::AddRotation(const glm::quat& rotation)
    {
        m_rotation = glm::normalize(rotation * m_rotation);
    }

    glm::mat4 Transform::CalculateModelMatrix() const
    {
        glm::mat4 mat = glm::mat4(1.0f);
        mat = glm::translate(mat, m_position);
        mat = mat * glm::toMat4(m_rotation);
        mat = glm::scale(mat, m_scale);

        if (m_parent)
            mat = m_parent->CalculateModelMatrix() * mat;

        return mat;
    }
} // namespace ny::ECS