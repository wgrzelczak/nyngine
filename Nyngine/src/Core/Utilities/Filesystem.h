#pragma once

#define NY_PATH(type, path) ny::Utilities::GetPath(ny::ResourceType::##type, path)

namespace ny
{
    enum class ResourceType
    {
        UNKNOWN,
        Shader,
        Texture,
        GLTF
    };
}

namespace ny::Utilities
{
    std::string GetPath(ResourceType type, std::string path);

    std::string ReadFileToString(const std::string& filename);
} // namespace ny::Utilities