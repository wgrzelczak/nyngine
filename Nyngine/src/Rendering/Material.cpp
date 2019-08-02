#include "pch.h"
#include "Material.h"

namespace ny::Rendering
{
    Material::Material(std::shared_ptr<MaterialShared> sharedMaterial) :
        m_sharedMaterialPtr(sharedMaterial)
    {
    }

    Material::Material(const Material& material) :
        m_sharedMaterialPtr(material.m_sharedMaterialPtr)
    {
    }

    void Material::Bind() const
    {
        m_sharedMaterialPtr->Bind();
    }
} // namespace ny::Rendering