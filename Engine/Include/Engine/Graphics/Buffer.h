#pragma once

#include <memory>
#include <stdexcept>

namespace Engine
{
    class InvalidBufferSize : public std::out_of_range
    {
    public:
        InvalidBufferSize(const std::string& message) : std::out_of_range(message) {}
        InvalidBufferSize(const char* message) : std::out_of_range(message) {}
    };

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