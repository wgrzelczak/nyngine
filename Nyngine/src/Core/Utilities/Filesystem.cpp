#include "pch.h"
#include "Filesystem.h"

std::string ny::Utilities::GetPath(ResourceType type, std::string path)
{
    const std::map<ResourceType, std::string> dirPaths{
        {ResourceType::UNKNOWN, ""},
        {ResourceType::Shader, "Assets/Shaders/"},
        {ResourceType::Texture, "Assets/Textures/"},
        {ResourceType::GLTF, "Assets/glTF/"}};

    return dirPaths.at(type) + path;
}

std::string ny::Utilities::ReadFileToString(const std::string& filename)
{
    // no feedback is provided for stream errors / exceptions.

    std::ifstream file(filename);
    if (!file) return std::string();

    file.ignore(std::numeric_limits<std::streamsize>::max());
    auto size = file.gcount();

    file.clear();
    file.seekg(0, std::ios_base::beg);

    std::stringstream sstr;
    sstr << file.rdbuf();
    file.close();

    return sstr.str();
}
