#include <Engine/Entity.h>

#include <Engine/World.h>

#include <algorithm>

void Engine::Entity::OnBegin()
{
}

void Engine::Entity::OnUpdate(const Engine::DeltaTime& deltaTime)
{
    std::ranges::for_each(m_ComponentsToRemove, [this](std::size_t hashCode) { this->m_Components.erase(hashCode); });
    m_ComponentsToRemove.clear();

    std::ranges::for_each(m_Components, [&deltaTime](auto& pair){ pair.second->OnUpdate(deltaTime); });
}

void Engine::Entity::OnRender()
{
    std::ranges::for_each(m_Components, [](auto& pair){ pair.second->OnRender(); });
}

void Engine::Entity::OnEnd()
{
    std::ranges::for_each(m_Components, [](auto& pair){ pair.second->OnEnd(); });
}

void Engine::Entity::Destroy()
{
    m_World->DestroyEntity(this);
}
