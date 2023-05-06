#include <Engine/DeltaTime.h>

void Engine::DeltaTime::UpdateDeltaTime() noexcept
{
    auto current = std::chrono::system_clock::now();

    if (m_Previous.time_since_epoch().count() > 0)
        m_DeltaTime = current - m_Previous;

    m_Previous = current;
}