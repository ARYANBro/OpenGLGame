#pragma once

#include <memory>

namespace Engine
{
    class Buffer
    {
    public:
        Buffer();
        Buffer(const void* data, unsigned int Size);

        Buffer(const Buffer&) noexcept = delete;
        Buffer(Buffer&&) noexcept = delete;
        virtual ~Buffer() noexcept;
        
        virtual void SetData(const void* data, unsigned int Size);
        unsigned int GetID() const noexcept { return m_ID; }

    protected:
        unsigned int m_ID = -1;
        const void* m_Data = nullptr;
        unsigned int m_Size = 0;
    };
}