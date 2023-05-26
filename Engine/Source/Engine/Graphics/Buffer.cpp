#include <Engine/Graphics/Buffer.h>

#include <Engine/Debug.h>

#include <glad/glad.h>

#include <stdexcept>
#include <cassert>
#include <limits>

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
        throw InvalidBufferSize("void Engine::Buffer::SetData(const void* data, unsigned int size) | size is invalid");

    if (m_Data)
        glNamedBufferSubData(m_ID, 0, size, data); // If data is already created just update it
    else
        glNamedBufferData(m_ID, size, data, GL_DYNAMIC_DRAW); // Else create new block of data

    m_Data = data;
    m_Size = size;
}
