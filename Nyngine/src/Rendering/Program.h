#pragma once
#include "Attributes.h"
#include "glm/glm.hpp"

namespace ny::Rendering
{
    class Program
    {
    public:
        Program(std::string vsFilename, std::string fsFilename);

        u32 m_programId{0};

        std::vector<Uniform> m_uniforms;
        std::vector<Attribute> m_attributes;

        void SetBool(std::string location, bool value) const;
        void SetInt(std::string location, i32 value) const;
        void SetUint(std::string location, u32 value) const;
        void SetFloat(std::string location, f32 value) const;
        void SetVector(std::string location, glm::vec2 value) const;
        void SetVector(std::string location, glm::vec3 value) const;
        void SetVector(std::string location, glm::vec4 value) const;
        void SetVectorArray(std::string location, i32 size, const std::vector<glm::vec2>& values) const;
        void SetVectorArray(std::string location, i32 size, const std::vector<glm::vec3>& values) const;
        void SetVectorArray(std::string location, i32 size, const std::vector<glm::vec4>& values) const;
        void SetMatrix(std::string location, glm::mat2 value) const;
        void SetMatrix(std::string location, glm::mat3 value) const;
        void SetMatrix(std::string location, glm::mat4 value) const;
        void SetMatrixArray(std::string location, i32 size, glm::mat2* values) const;
        void SetMatrixArray(std::string location, i32 size, glm::mat3* values) const;
        void SetMatrixArray(std::string location, i32 size, glm::mat4* values) const;

    private:
        void RetrieveAttributes();
        void RetrieveUniforms();

        i32 GetUniformLocation(const std::string& name) const;
    };
} // namespace ny::Rendering