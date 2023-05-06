#pragma once

#include <vector>
#include <memory>
#include <list>

namespace Engine
{
    class VertexBuffer;
    class IndexBuffer;

    enum class VertexAttributeType
    {
        Float
    };

    struct VertexAttributeFormat
    {
        unsigned int AttributeIndex;
        unsigned int Size;
        VertexAttributeType Type;
        bool Normalized;
        unsigned int RelativeOffset;
    };

    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray() noexcept;

        // Returns the index of the vertex buffer
        unsigned int AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer, unsigned int offset, unsigned int stride);
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
        void BindAttribute(unsigned int attribIndex, unsigned int bufferIndex) const;
        void SetAttributeFormat(VertexAttributeFormat format) const;
        void SetAttributeFormats(const std::list<VertexAttributeFormat>& formats) const;
        void EnableAttribute(unsigned int attribIndex) const;
        void Bind() const;
        void Unbind() const;
        const VertexBuffer& GetVertexBuffer(unsigned int index) const { return *m_VertexBuffers.at(index); }
        const IndexBuffer& GetIndexBuffer() const { return *m_IndexBuffer; }

    private:
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        unsigned int m_ID = 0;
    };
}