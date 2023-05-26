#include <Engine/Graphics/Shader.h>

#include <Engine/Debug.h>

#include <glad/glad.h>

#include <cassert>
#include <fstream>
#include <sstream>

Engine::Shader::Shader(ShaderType type)
{
    switch (type)
    {
    case ShaderType::VertexShader:
        m_ID = glCreateShader(GL_VERTEX_SHADER);
        break;

    case ShaderType::FragmentShader:
        m_ID = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    
    default:
        assert(false);
        break;
    }
}

Engine::Shader::Shader(const std::string& filePath, ShaderType type)
    : Shader(type)
{
    SetSourceCode(filePath);
}

Engine::Shader::~Shader() noexcept
{
    glDeleteShader(m_ID);
}

void Engine::Shader::SetSourceCode(const std::string& filePath)
{
    std::ifstream iFile;
    iFile.exceptions(std::ios::badbit | std::ios::failbit);
    iFile.open(filePath);

    std::stringstream sstream;
    sstream << iFile.rdbuf();

    m_SourceCode = sstream.str();

    const char* srcCodePtr = m_SourceCode.c_str();
    glShaderSource(m_ID, 1, &srcCodePtr, nullptr);
    glCompileShader(m_ID);

    if (std::string error = CheckError(); !error.empty())
        throw ShaderCompileError("Shader Compile Error: " + filePath + " |: " + error);

    PRINT_INFO(filePath + " Shader compiled successfuly");
}

std::string Engine::Shader::CheckError() const
{
    GLint compileStatus;
    glGetShaderiv(m_ID, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_TRUE)
        return {};

    GLint logLength;
    glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &logLength);
    std::string error;
    error.resize(logLength);
    glGetShaderInfoLog(m_ID, logLength, &logLength, &error[0]);

    return error;
}