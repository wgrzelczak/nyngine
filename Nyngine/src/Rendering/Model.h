#pragma once
#include "Material.h"
#include "Mesh.h"
#include "Preinclude.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace ny::Rendering
{
    class Model
    {
    public:
        Model();
        Model(Material* material, Mesh* mesh);

        void SetPosition(const glm::vec3& position);
        void SetRotationAroundAxis(const f32& angle, const glm::vec3& axis);
        void SetQuaternionRotation(const glm::quat& rotation);
        void SetScale(const glm::vec3& scale);

        void SetMaterial(Material* material);
        void SetMesh(Mesh* mesh);

        void AddRotation(const glm::quat& rotation);

        void CalculateModelMatrix();

        glm::mat4 GetModelMatrix() const;
        Mesh* GetMesh() const;

    private:
        glm::vec3 m_position{0.0f, 0.0f, 0.0f};
        glm::quat m_rotation{0.0f, 0.0f, 0.0f, 1.0f};
        glm::vec3 m_scale{0.0f, 0.0f, 0.0f};

        glm::mat4 m_modelMatrix{1.0f};

        Material* m_material = nullptr;
        Mesh* m_mesh = nullptr;
    };
} // namespace ny::Rendering