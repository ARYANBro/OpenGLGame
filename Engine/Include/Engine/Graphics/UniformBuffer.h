#pragma once

#include "Buffer.h"

namespace Engine
{
    class UniformBuffer : public Buffer
    {
    public:
        void Bind(unsigned int slot);
    };
}