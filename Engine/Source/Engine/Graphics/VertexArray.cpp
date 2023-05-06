#include <Engine/Graphics/VertexArray.h>

#include <Engine/Graphics/VertexBuffer.h>
#include <Engine/Graphics/IndexBuffer.h>

#include <glad/glad.h>

#include <cassert>

Engine::VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_ID);
}

Engine::VertexArray::~VertexArray() noexcept
{
    glDeleteBuffers(1, &m_ID);
    glDeleteVertexArrays(1, &m_ID);
}

unsigned int Engine::VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer, unsigned int offset, unsigned int stride)
{
    unsigned int index = static_cast<unsigned int>(m_VertexBuffers.size());
    glVertexArrayVertexBuffer(m_ID, index, buffer->GetID(), offset, stride);
    m_VertexBuffers.push_back(buffer);
    return index;
}

void Engine::VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
{
    m_IndexBuffer = buffer;
    glVertexArrayElementBuffer(m_ID, buffer->GetID());
}

void Engine::VertexArray::BindAttribute(unsigned int attribIndex, unsigned int bufferIndex) const
{
    glVertexArrayAttribBinding(m_ID, attribIndex, bufferIndex);
}

void Engine::VertexArray::SetAttributeFormat(VertexAttributeFormat format) const
{
    GLenum type;
    switch (format.Type)
    {
    case VertexAttributeType::Float:
        type = GL_FLOAT;
        break;

    default:
        assert(false);
    }

    glVertexArrayAttribFormat(m_ID, format.AttributeIndex, format.Size, type, format.Normalized, format.RelativeOffset);
}

void Engine::VertexArray::SetAttributeFormats(const std::list<VertexAttributeFormat>& formats) const
{
    unsigned int idx = 0;
    for (const VertexAttributeFormat& format : formats)
    {
        SetAttributeFormat(format);
        EnableAttribute(idx++);
    }
}

void Engine::VertexArray::EnableAttribute(unsigned int attribIndex) const
{
    glEnableVertexArrayAttrib(m_ID, attribIndex);
}

void Engine::VertexArray::Bind() const
{
    glBindVertexArray(m_ID);
}

void Engine::VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
