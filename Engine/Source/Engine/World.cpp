#include <Engine/World.h>

#include <Engine/DeltaTime.h>
#include <Engine/Entity.h>

#include <algorithm>

bool Engine::World::DestroyEntity(Entity* entity)
{
    auto&& [it, result] = m_EntitiesToDestroy.insert(entity);
    return result;
}

void Engine::World::OnBegin()
{
}

void Engine::World::Update(const DeltaTime& deltaTime)
{
    std::ranges::for_each(m_Entities, [&deltaTime](auto&& pair) { pair.first->OnUpdate(deltaTime); });
    std::ranges::for_each(m_EntitiesToDestroy, [this, &deltaTime](Entity* entity) { this->m_Entities.erase(entity); });
    m_EntitiesToDestroy.clear();
}

void Engine::World::OnRender()
{
    std::ranges::for_each(m_Entities, [](auto&& pair) { pair.first->OnRender(); });
}

void Engine::World::OnEnd()
{
    std::ranges::for_each(m_Entities, [](auto&& pair) { pair.first->OnEnd(); });
}
