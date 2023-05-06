#pragma once

#include "Buffer.h"

namespace Engine
{
    class IndexBuffer : public Buffer
    {
    public:
        IndexBuffer(const void* data, unsigned int size, unsigned int count)
            : Buffer(data, size) { SetCount(count); }

        void SetCount(unsigned int count) noexcept { m_Count = count; }
        unsigned int GetCount() const noexcept { return m_Count; }
    private:
        unsigned int m_Count;
    };
}