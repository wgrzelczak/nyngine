#include "pch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace ny::Rendering
{
    Texture::Texture(std::string filename)
    {
        stbi_set_flip_vertically_on_load(true);
        m_data = stbi_load(filename.c_str(), &m_width, &m_height, &m_channelsNumber, 0);
        NY_ASSERT(m_data != nullptr, "Cannot load texture {}", filename);
    }

    Texture::~Texture()
    {
        if (m_data)
            UnloadData();
    }

    void Texture::UnloadData()
    {
        stbi_image_free(m_data);
        m_data = nullptr;
    }
} // namespace ny::Rendering