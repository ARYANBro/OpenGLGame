#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>

namespace Engine
{
    class Entity;

    class World
    {
    public:
        template<typename EntityType>
        EntityType* CreateEntity() requires std::is_base_of_v<Entity, EntityType>
        {
            EntityType* newEntity = new EntityType(this);
            m_Entities.emplace(newEntity, std::unique_ptr<EntityType>(newEntity));
            newEntity->OnBegin();
            return newEntity;
        }

        bool DestroyEntity(Entity* entity);
        void OnBegin();
        void Update(const class DeltaTime& deltaTime);
        void OnRender();
        void OnEnd();

    private:
        std::unordered_map<Entity*, std::unique_ptr<Entity>> m_Entities;
        std::unordered_set<Entity*> m_EntitiesToDestroy;
    };
}