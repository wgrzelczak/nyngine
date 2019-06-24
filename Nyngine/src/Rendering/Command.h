#pragma once
#include "Preinclude.h"
#include "Material.h"
#include "Mesh.h"

namespace ny::Rendering
{
    struct Command
    {
        Material* m_material{nullptr};
        Mesh* m_mesh{nullptr};
        glm::mat4 m_transform{1.0f};

        Command() {}

        Command(Material* material, Mesh* mesh, glm::mat4 transform) :
            m_material(material), m_mesh(mesh), m_transform(transform)
        {
        }
    };
} // namespace ny::Rendering