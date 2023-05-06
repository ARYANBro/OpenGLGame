#pragma once

#include "Component.h"
#include "MeshComponent.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Shader.h"

#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace Engine
{
    class World;

    class Entity
    {
    public:
        Entity(World* world) noexcept
            : m_World(world) {}

        virtual ~Entity() noexcept = default;

        virtual void OnBegin();
        virtual void OnUpdate(const class DeltaTime& deltaTime);
        virtual void OnRender();
        virtual void OnEnd();

        void Destroy();

        template<typename ComponentType>
        ComponentType* AddComponent()
        {
            if (auto component = GetComponent<ComponentType>(); component != nullptr)
                return component;

            ComponentType* component = new ComponentType(*this);
            m_Components.emplace(typeid(ComponentType).hash_code(), std::unique_ptr<ComponentType>(component));
            component->OnBegin();
            return component;
        }

        template<typename ComponentType>
        ComponentType* GetComponent() const
        {
            auto it = m_Components.find(typeid(ComponentType).hash_code());
            if (it == m_Components.end())
                return nullptr;
            return reinterpret_cast<ComponentType*>(it->second.get());
        }

        template<typename ComponentType>
        bool RemoveComponent()
        {
            ComponentType* component = GetComponent<ComponentType>();

            if (!component)
                component->OnEnd();

            auto result = m_ComponentsToRemove.insert(typeid(ComponentType).hash_code());
            return result.second;
        }

    private:
        World* m_World;
        std::unordered_map<std::size_t, std::unique_ptr<class Component>> m_Components;
        std::unordered_set<std::size_t> m_ComponentsToRemove;
    };
}