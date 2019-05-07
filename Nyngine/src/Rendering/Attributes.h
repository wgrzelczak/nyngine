#pragma once
#include "Preinclude.h"
#include "glad/glad.h"

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

    inline GLSLType GetGLSLType(GLenum value)
    {
        switch (value)
        {
        case GL_INT:
            return GLSLType::Int;
        case GL_UNSIGNED_INT:
            return GLSLType::Uint;
        case GL_FLOAT:
            return GLSLType::Float;
        case GL_FLOAT_VEC2:
            return GLSLType::Vec2;
        case GL_FLOAT_VEC3:
            return GLSLType::Vec3;
        case GL_FLOAT_VEC4:
            return GLSLType::Vec4;
        case GL_FLOAT_MAT2:
            return GLSLType::Mat2;
        case GL_FLOAT_MAT3:
            return GLSLType::Mat3;
        case GL_FLOAT_MAT4:
            return GLSLType::Mat4;

        case GL_FLOAT_MAT2x3:
        case GL_FLOAT_MAT2x4:
        case GL_FLOAT_MAT3x2:
        case GL_FLOAT_MAT3x4:
        case GL_FLOAT_MAT4x2:
        case GL_FLOAT_MAT4x3:
        case GL_INT_VEC2:
        case GL_INT_VEC3:
        case GL_INT_VEC4:
        case GL_UNSIGNED_INT_VEC2:
        case GL_UNSIGNED_INT_VEC3:
        case GL_UNSIGNED_INT_VEC4:
        default:
            return GLSLType::Undefined;
        }
    }

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