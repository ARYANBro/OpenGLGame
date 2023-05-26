#pragma once

#include <string>

#include <stdexcept>

namespace Engine
{
    class ShaderCompileError : public std::runtime_error
    {
    public:
        ShaderCompileError(const std::string& message) : std::runtime_error(message) {}
        ShaderCompileError(const char* message) : std::runtime_error(message) {}
    };

    enum class ShaderType
    {
        VertexShader,
        FragmentShader
    };

    class Shader
    {
    public:
        Shader(ShaderType type);
        Shader(const std::string& filePath, ShaderType type);
        ~Shader() noexcept;

        void SetSourceCode(const std::string& filePath);
        const std::string& GetSourceCode() const noexcept { return m_SourceCode; }
        unsigned int GetID() const noexcept { return m_ID; }
    
    private:
        std::string CheckError() const;

    private:
        unsigned int m_ID;
        std::string m_SourceCode;
    };
}