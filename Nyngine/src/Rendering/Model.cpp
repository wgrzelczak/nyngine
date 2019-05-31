#include "pch.h"
#include "Model.h"
#include "ModelLoader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

namespace ny::Rendering
{
    Model::Model()
    {
    }

    Model::Model(Material* material, Mesh* mesh) :
        m_material(material), m_mesh(mesh)
    {
        m_mesh->Generate();
    }

    Model::Model(Material* material, std::string filename) :
        m_material(material), m_mesh(new Mesh())
    {
        ModelLoader::LoadModel(*this, filename);
        m_mesh->Generate();
    }

    void Model::SetPosition(const glm::vec3& position)
    {
        m_position = position;
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
        m_rotation = glm::normalize(rotation * m_rotation);
    }

    glm::mat4 Model::GetModelMatrix() const
    {
        return m_modelMatrix;
    }

    Mesh* Model::GetMesh() const
    {
        return m_mesh;
    }

    Material* Model::GetMaterial() const
    {
        return m_material;
    }

    glm::quat& Model::GetRotationRef()
    {
        return m_rotation;
    }

    void Model::NormalizeRotation()
    {
        m_rotation = glm::normalize(m_rotation);
    }

    void Model::CalculateModelMatrix()
    {
        m_modelMatrix = glm::mat4(1.0f);
        m_modelMatrix = glm::translate(m_modelMatrix, m_position);
        m_modelMatrix = m_modelMatrix * glm::toMat4(m_rotation);
        m_modelMatrix = glm::scale(m_modelMatrix, m_scale);

        //m_modelMatrix = parent->GetModelMatrix() * m_modelMatrix;
    }

} // namespace ny::Rendering