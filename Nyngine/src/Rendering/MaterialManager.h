#pragma once
#include "Preinclude.h"
#include "Material.h"
#include "MaterialShared.h"

namespace ny::Rendering
{
    std::shared_ptr<Material> GetMaterial(const std::string& vs, const std::string& fs);

    class MaterialManager
    {
    public:
        std::shared_ptr<Material> CreateMaterial(const std::string& vs, const std::string& fs);
        std::shared_ptr<Material> CreateMaterial(const Material& base);

    private:
        std::shared_ptr<MaterialShared> ReceiveSharedMaterialPtr(const std::string& vs, const std::string& fs);

        std::map<MaterialHash, std::shared_ptr<MaterialShared>> m_sharedMaterials;
        struct HelperMaterialCmp
        {
            bool operator()(const std::shared_ptr<Material>& lhs, const std::shared_ptr<Material>& rhs) const
            {
                return lhs.get() < rhs.get();
            }
        };
        std::set<std::shared_ptr<Material>, HelperMaterialCmp> m_materials;
    };
} // namespace ny::Rendering

namespace ny
{
    using MaterialManager = Rendering::MaterialManager;
}