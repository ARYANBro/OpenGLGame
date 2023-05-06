#pragma once

#include "Buffer.h"

namespace Engine
{
    class VertexBuffer : public Buffer
    {
    public:
        VertexBuffer()
            : Buffer() {}

        VertexBuffer(const void* data, unsigned int size, unsigned int count);
        void Bind() const;
        void Unbind() const;
        void SetCount(unsigned int count);
        unsigned int GetCount() const noexcept { return m_Count; }
        
    private:
        unsigned int m_Count;
    };
}