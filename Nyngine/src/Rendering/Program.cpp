#pragma once
#include "pch.h"
#include "Program.h"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

namespace ny::Rendering
{
    Program::Program(std::string vsFilename, std::string fsFilename)
    {
        Shader vShader = Shader(vsFilename, ShaderType::Vertex);
        Shader fShader = Shader(fsFilename, ShaderType::Fragment);

        m_programId = glCreateProgram();
        glAttachShader(m_programId, vShader.m_shaderId);
        glAttachShader(m_programId, fShader.m_shaderId);

        glLinkProgram(m_programId);
        Shader::CheckLinkingError(m_programId);

        glDeleteShader(vShader.m_shaderId);
        glDeleteShader(fShader.m_shaderId);

        RetrieveAttributes();
        RetrieveUniforms();
    }

    void Program::RetrieveAttributes()
    {
        i32 attribsNum{0};
        glGetProgramiv(m_programId, GL_ACTIVE_ATTRIBUTES, &attribsNum);

        m_attributes.reserve(attribsNum);

        char buffer[128];
        GLenum glType;
        i32 glSize;
        u32 glLocation;

        for (u32 i{0}; i < attribsNum; ++i)
        {
            glGetActiveAttrib(m_programId, i, sizeof(buffer), 0, &glSize, &glType, buffer);
            glLocation = glGetAttribLocation(m_programId, buffer);

            m_attributes.emplace_back(GetGLSLType(glType), std::string(buffer), glSize, glLocation);
        }
    }

    void Program::RetrieveUniforms()
    {
        i32 uniformsNum{0};
        glGetProgramiv(m_programId, GL_ACTIVE_UNIFORMS, &uniformsNum);

        m_uniforms.reserve(uniformsNum);

        char buffer[128];
        GLenum glType;
        i32 glSize;
        u32 glLocation;

        for (u32 i{0}; i < uniformsNum; ++i)
        {
            glGetActiveUniform(m_programId, i, sizeof(buffer), 0, &glSize, &glType, buffer);
            glLocation = glGetUniformLocation(m_programId, buffer);

            m_uniforms.emplace_back(GetGLSLType(glType), std::string(buffer), glSize, glLocation);
        }
    }

    i32 Program::GetUniformLocation(const std::string& name) const
    {
        for (const auto& u : m_uniforms)
        {
            if (u.m_name == name) return u.m_location;
        }
        return {-1};
    }

    void Program::SetBool(std::string location, bool value) const
    {
        SetInt(location, static_cast<i32>(value));
    }

    void Program::SetInt(std::string location, i32 value) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniform1i(loc, value);
    }

    void Program::SetUint(std::string location, i32 value) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniform1ui(loc, value);
    }

    void Program::SetFloat(std::string location, f32 value) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniform1f(loc, value);
    }

    void Program::SetVector(std::string location, glm::vec2 value) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniform2fv(loc, 1, &value[0]);
    }

    void Program::SetVector(std::string location, glm::vec3 value) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniform3fv(loc, 1, &value[0]);
    }

    void Program::SetVector(std::string location, glm::vec4 value) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniform4fv(loc, 1, &value[0]);
    }

    void Program::SetVectorArray(std::string location, i32 size, const std::vector<glm::vec2>& values) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniform2fv(loc, size, &values[0][0]);
    }

    void Program::SetVectorArray(std::string location, i32 size, const std::vector<glm::vec3>& values) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniform3fv(loc, size, &values[0][0]);
    }

    void Program::SetVectorArray(std::string location, i32 size, const std::vector<glm::vec4>& values) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniform4fv(loc, size, &values[0][0]);
    }

    void Program::SetMatrix(std::string location, glm::mat2 value) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniformMatrix2fv(loc, 1, GL_FALSE, &value[0][0]);
    }

    void Program::SetMatrix(std::string location, glm::mat3 value) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::SetMatrix(std::string location, glm::mat4 value) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::SetMatrixArray(std::string location, i32 size, glm::mat2* values) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniformMatrix2fv(loc, size, GL_FALSE, glm::value_ptr(values[0]));
    }

    void Program::SetMatrixArray(std::string location, i32 size, glm::mat3* values) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniformMatrix4fv(loc, size, GL_FALSE, glm::value_ptr(values[0]));
    }

    void Program::SetMatrixArray(std::string location, i32 size, glm::mat4* values) const
    {
        int loc = GetUniformLocation(location);
        if (loc >= 0)
            glUniformMatrix4fv(loc, size, GL_FALSE, &values[0][0][0]);
    }
} // namespace ny::Rendering