#pragma once

#include <Engine/Debug.h>

namespace Engine
{
    class Entity;

    class Component
    {
    public:
        Component(const Entity& entity) noexcept
            : m_Entity(entity) {}

        virtual ~Component() noexcept = default;

        virtual void OnBegin() {}
        virtual void OnUpdate(const class DeltaTime& deltaTime) {}
        virtual void OnRender() {}
        virtual void OnEnd() {}
    
    protected:
        const Entity& m_Entity;
    };
}