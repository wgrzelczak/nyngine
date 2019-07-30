#pragma once
#include "Preinclude.h"

#define GL_ATTRIB_LOCATION_POSITION (0)
#define GL_ATTRIB_LOCATION_NORMALS (1)
#define GL_ATTRIB_LOCATION_TEXCOORDS0 (2)
#define GL_ATTRIB_LOCATION_TEXCOORDS1 (3)

#define GL_ATTRIB_NUM (4)

namespace ny::Rendering
{
    enum class GLSLType
    {
        Undefined,
        Int,
        Uint,
        Float,
        Sampler1d,
        Sampler2d,
        Sampler3d,
        //Samplercube,
        Vec2,
        Vec3,
        Vec4,
        Mat2,
        Mat3,
        Mat4
    };

    GLSLType GetGLSLType(unsigned int value);

    struct Attribute
    {
        GLSLType m_type = GLSLType::Undefined;
        std::string m_name = "Undefined";
        i32 m_size = 0;
        u32 m_location = 0;

        Attribute(GLSLType type, std::string name, i32 size, u32 loc) :
            m_type(type), m_name(std::move(name)), m_size(size), m_location(loc)
        {
        }
    };

    struct Uniform
    {
        GLSLType m_type = GLSLType::Undefined;
        std::string m_name = "Undefined";
        i32 m_size = 0;
        u32 m_location = 0;

        Uniform(GLSLType type, std::string name, i32 size, u32 loc) :
            m_type(type), m_name(std::move(name)), m_size(size), m_location(loc)
        {
        }
    };
} // namespace ny::Rendering