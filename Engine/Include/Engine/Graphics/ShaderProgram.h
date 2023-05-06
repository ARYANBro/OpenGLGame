#pragma once

#include <string>

#include <Engine/Math/MathTypes.h>

namespace Engine
{
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
        void SetMatrix4(const std::string& name, const Math::Matrix4& value) const;

    private:
        std::string CheckError() const;
        int GetUniformLocation(const std::string& name) const;

    private:
        unsigned int m_ID;
    };
}
