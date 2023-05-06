#pragma once

#include <chrono>

namespace Engine
{
    class DeltaTime
    {
    public:
        void UpdateDeltaTime() noexcept;
        operator float() const noexcept { return m_DeltaTime.count(); }

    private:
        mutable std::chrono::system_clock::time_point m_Previous;
        std::chrono::duration<float> m_DeltaTime = {};
    };
}