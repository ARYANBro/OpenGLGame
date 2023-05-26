#include <Engine/Graphics/VertexBuffer.h>

#include <glad/glad.h>

#include <stdexcept>

Engine::VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int count)
    : Buffer(data, size)
{
    SetCount(count);
}

void Engine::VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void Engine::VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::VertexBuffer::SetCount(unsigned int count)
{
    if (count == std::numeric_limits<unsigned int>::max())
        throw InvalidBufferSize("void Engine::VertexBuffer::SetCount(unsigned int count) | count is invalid");

    m_Count = count;
}