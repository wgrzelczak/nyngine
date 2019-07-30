#include "pch.h"
#include "Attributes.h"
#include "glad/glad.h"

namespace ny::Rendering
{
    GLSLType GetGLSLType(unsigned int value)
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
} // namespace ny::Rendering