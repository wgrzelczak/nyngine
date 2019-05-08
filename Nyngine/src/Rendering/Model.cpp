#include "pch.h"
#include "Model.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

namespace ny::Rendering
{
    Model::Model()
    {
    }

    Model::Model(Material* material, Mesh* mesh) :
        m_material(material), m_mesh(mesh)
    {
    }

    void Model::SetPosition(const glm::vec3& position)
    {
        m_position = position;
    }

    void Model::SetRotationAroundAxis(const f32& angle, const glm::vec3& axis)
    {
        m_rotation = glm::angleAxis(angle, axis);
    }

    void Model::SetQuaternionRotation(const glm::quat& rotation)
    {
        m_rotation = rotation;
    }

    void Model::SetScale(const glm::vec3& scale)
    {
        m_scale = scale;
    }

    void Model::SetMaterial(Material* material)
    {
        m_material = material;
    }

    void Model::SetMesh(Mesh* mesh)
    {
        m_mesh = mesh;
    }

    void Model::AddRotation(const glm::quat& rotation)
    {
        m_rotation += rotation;
    }

    glm::mat4 Model::GetModelMatrix() const
    {
        return m_modelMatrix;
    }

    Mesh* Model::GetMesh() const
    {
        return m_mesh;
    }

    void Model::CalculateModelMatrix()
    {
        m_modelMatrix = glm::mat4(1.0f);
        m_modelMatrix = glm::translate(m_modelMatrix, m_position);
        m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.w, {m_rotation.x, m_rotation.y, m_rotation.z});
        m_modelMatrix = glm::scale(m_modelMatrix, m_scale);

        //m_modelMatrix = parent->GetModelMatrix() * m_modelMatrix;
    }

} // namespace ny::Rendering