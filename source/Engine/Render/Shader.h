#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ResourceManager.h"
#include "ResourceType.h"

using namespace std;

class Shader
{
private:
	unsigned int shaderId;
public:
    Shader(const string& vertexName, const string& fragmentName);
    
    ~Shader()
    {
        glDeleteProgram(shaderId);
    }

    void use() const
    {
        glUseProgram(shaderId);
    }

    unsigned int getShaderId() { return shaderId; }

    void setBool(const string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);
    }

    void setInt(const string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
    }

    void setFloat(const string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
    }

    void setVec2(const string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
    }
    void setVec2(const string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(shaderId, name.c_str()), x, y);
    }

    void setVec3(const string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
    }
    void setVec3(const string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(shaderId, name.c_str()), x, y, z);
    }

    void setVec4(const string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
    }
    void setVec4(const string& name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(shaderId, name.c_str()), x, y, z, w);
    }

    void setMat2(const string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
};