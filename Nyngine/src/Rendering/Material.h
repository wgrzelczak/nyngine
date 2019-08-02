#pragma once
#include "MaterialShared.h"

namespace ny::Rendering
{
    class Material
    {
    public:
        Material(std::shared_ptr<MaterialShared> sharedMaterial);
        Material(const Material& material);

        void Bind() const;
        Program& GetProgram() const { return m_sharedMaterialPtr->GetProgram(); }

        std::shared_ptr<MaterialShared> GetSharedMaterial() const { return m_sharedMaterialPtr; }

    private:
        std::shared_ptr<MaterialShared> m_sharedMaterialPtr;
    };
} // namespace ny::Rendering