#include <Engine/Graphics/Buffer.h>

#include <Engine/Debug.h>

#include <glad/glad.h>

#include <stdexcept>
#include <cassert>
#include <limits>

// Engine::Buffer::Buffer(BufferType type)
//     : m_BufferType(type)
// {
//     glCreateBuffers(1, &m_ID);
// }

// Engine::Buffer::Buffer(VertexBufferData data)
//     : Buffer(BufferType::VertexBuffer)
// {
//     SetData(data);
// }

// Engine::Buffer::Buffer(UniformBufferData data)
//     : Buffer(BufferType::UniformBuffer)
// {
//     SetData(data);
// }

Engine::Buffer::Buffer()
{
    glCreateBuffers(1, &m_ID);
}

Engine::Buffer::Buffer(const void* data, unsigned int size)
    : Buffer()
{
    SetData(data, size);
}

Engine::Buffer::~Buffer() noexcept
{
    glDeleteBuffers(1, &m_ID);
}

void Engine::Buffer::SetData(const void* data, unsigned int size)
{
    if (size == std::numeric_limits<unsigned int>::max())
        throw std::invalid_argument("void Engine::Buffer::SetData(const void* data, unsigned int size) | size is invalid");
    m_Data = data;
    m_Size = size;

    glNamedBufferData(m_ID, size, data, GL_DYNAMIC_DRAW);
}
