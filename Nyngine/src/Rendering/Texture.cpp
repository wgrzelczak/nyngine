#include "pch.h"
#include "Texture.h"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace ny::Rendering
{
    Texture::Texture(std::string filename) :
        m_name(filename)
    {
        NY_INFO("[Resources] Loading texture {}...", m_name);
        stbi_set_flip_vertically_on_load(false);
        m_data = stbi_load(filename.c_str(), &m_width, &m_height, &m_channelsNumber, 0);
        NY_ASSERT(m_data != nullptr, "Cannot load texture {}, reason: {}", filename, stbi_failure_reason());

        GenerateTexture();
        NY_INFO("[Resources] Texture {} loaded", m_name);
    }

    Texture::~Texture()
    {
        if (m_data)
            UnloadData();
    }

    void Texture::UnloadData()
    {
        NY_INFO("[Resources] Unloading texture {}...", m_name);
        stbi_image_free(m_data);
        m_data = nullptr;
        NY_INFO("[Resources] Texture {} unloaded", m_name);
    }

    void Texture::GenerateTexture()
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
} // namespace ny::Rendering