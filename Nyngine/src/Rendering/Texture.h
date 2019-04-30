#pragma once
#include "Preinclude.h"

namespace ny::Rendering
{
    class Texture
    {
    public:
        Texture(std::string filename);
        ~Texture();
        void UnloadData();

        i32 m_width = 0;
        i32 m_height = 0;
        i32 m_channelsNumber = 0;

        unsigned char* m_data = nullptr;
    };
} // namespace ny::Rendering