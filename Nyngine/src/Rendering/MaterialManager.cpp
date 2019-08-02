#include "pch.h"
#include "MaterialManager.h"
#include "Core/Engine.h"
#include "Material.h"
#include "Texture.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    std::shared_ptr<MaterialShared> MaterialManager::ReceiveSharedMaterialPtr(const std::string& vs, const std::string& fs)
    {
        auto hash = CalcluateMaterialHash(vs, fs);

        if (auto ptr = m_sharedMaterials.find(hash); ptr != std::end(m_sharedMaterials)) //contains(), waiting for cpp20
            return ptr->second;

        return m_sharedMaterials.emplace(hash, std::make_shared<MaterialShared>(vs, fs)).first->second;
    }

    std::shared_ptr<Material> MaterialManager::CreateMaterial(const std::string& vs, const std::string& fs)
    {
        auto sharedMaterial = ReceiveSharedMaterialPtr(vs, fs);
        return *m_materials.emplace(std::make_shared<Material>(sharedMaterial)).first;
    }

    std::shared_ptr<Material> MaterialManager::CreateMaterial(const Material& base)
    {
        return *m_materials.emplace(std::make_shared<Material>(base)).first;
    }

    std::shared_ptr<Material> GetMaterial(const std::string& vs, const std::string& fs)
    {
        return Engine::GetInstance()->GetMaterialManager().CreateMaterial(vs, fs);
    }

} // namespace ny::Rendering