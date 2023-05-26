#pragma once

#include <glm/glm.hpp>

#include <string>
#include <stdexcept>

namespace Engine
{
    class ShaderLinkError : public std::runtime_error
    {
    public:
        ShaderLinkError(const std::string& name) : std::runtime_error(name) {}
        ShaderLinkError(const char* name) : std::runtime_error(name) {}
    };

    class ShaderUniformNotFound  : public std::runtime_error
    {
    public:
        ShaderUniformNotFound(const std::string& name) : std::runtime_error(name) {}
        ShaderUniformNotFound(const char* name) : std::runtime_error(name) {}
    };

    class ShaderProgram
    {
    public:
        ShaderProgram();
        ~ShaderProgram() noexcept;

        void AttachShader(const class Shader& shader) const;
        void Bind() const;
        void Unbind() const;
        void Link() const;

        void SetUniformBufferSlot(const std::string& name, unsigned int slot) const;

        void SetFloat(const std::string& name, float value) const;
        void SetMatrix4(const std::string& name, const glm::mat4& value) const;

    private:
        std::string CheckError() const;
        int GetUniformLocation(const std::string& name) const;

    private:
        unsigned int m_ID;
    };
}
