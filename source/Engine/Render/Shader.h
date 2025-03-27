#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

#include "Util/Header/Common.h"

namespace Engine
{
    class Shader
    {
    public:
        void Use() const { glUseProgram(shaderId); }
        uint32_t GetShaderId() { return shaderId; }
        void SetShaderId(uint32_t id) { shaderId = id; }

        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetVec2(const std::string& name, const glm::vec2& value) const;
        void SetVec2(const std::string& name, float x, float y) const;
        void SetVec3(const std::string& name, const glm::vec3& value) const;
        void SetVec3(const std::string& name, float x, float y, float z) const;
        void SetVec4(const std::string& name, const glm::vec4& value) const;
        void SetVec4(const std::string& name, float x, float y, float z, float w) const;
        void SetMat2(const std::string& name, const glm::mat2& mat) const;
        void SetMat3(const std::string& name, const glm::mat3& mat) const;
        void SetMat4(const std::string& name, const glm::mat4& mat) const;

        Shader();
        ~Shader() { glDeleteProgram(shaderId); }

    private:
        uint32_t shaderId;
    };
}