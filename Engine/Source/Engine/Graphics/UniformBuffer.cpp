#include <Engine/Graphics/UniformBuffer.h>

#include <glad/glad.h>

void Engine::UniformBuffer::Bind(unsigned int slot)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, slot, m_ID);
}