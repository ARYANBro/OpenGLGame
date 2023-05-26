#include <Engine/Graphics/ShaderProgram.h>

#include <Engine/Graphics/Shader.h>
#include <Engine/Debug.h>

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <cassert>

Engine::ShaderProgram::ShaderProgram()
{
    m_ID = glCreateProgram();
}

Engine::ShaderProgram::~ShaderProgram() noexcept
{
    glDeleteProgram(m_ID);
}

void Engine::ShaderProgram::AttachShader(const Shader& shader) const
{
    glAttachShader(m_ID, shader.GetID());
}

void Engine::ShaderProgram::Bind() const
{
    glUseProgram(m_ID);
}

void Engine::ShaderProgram::Unbind() const
{
    glUseProgram(0);
}

void Engine::ShaderProgram::Link() const
{
    glLinkProgram(m_ID);

    if (std::string error = CheckError(); !error.empty())
        throw ShaderLinkError("Shader Link Error | " + error);

    PRINT_INFO("Shader linked successfuly")
}

void Engine::ShaderProgram::SetUniformBufferSlot(const std::string& name, unsigned int slot) const
{
    glUniformBlockBinding(m_ID, glGetUniformBlockIndex(m_ID, name.c_str()), slot);
}

void Engine::ShaderProgram::SetFloat(const std::string& name, float value) const
{
    glProgramUniform1f(m_ID, GetUniformLocation(name), value);
}

void Engine::ShaderProgram::SetMatrix4(const std::string& name, const glm::mat4& value) const
{
    
    glProgramUniformMatrix4fv(m_ID, GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

std::string Engine::ShaderProgram::CheckError() const
{
    GLint linkStatus;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_TRUE)
        return {};

    GLint logLength;
    glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &logLength);
    std::string error;
    error.resize(logLength);
    glGetProgramInfoLog(m_ID, logLength, &logLength, &error[0]);
    return error;
}

int Engine::ShaderProgram::GetUniformLocation(const std::string& name) const
{
    int location = glGetUniformLocation(m_ID, name.c_str());
    if (location == -1)
        throw ShaderUniformNotFound("Shader Error | Could not find uniform \""  + name + "\" location");
    return location;
}