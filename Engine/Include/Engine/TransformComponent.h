#pragma once

#include "Component.h"

#include <glm/glm.hpp>

namespace Engine
{
    class TransformComponent : public Component
    {
    public:
        TransformComponent(const class Entity& entity) noexcept
            : Component(entity) {}
            
        virtual ~TransformComponent() noexcept override = default;

        void SetTranslation(const glm::vec3& translation) noexcept { m_Translation = translation; }
        void SetScale(const glm::vec3& scale) noexcept { m_Scale = scale;}
        void SetRotation(const glm::vec3& rotation) noexcept { m_Rotation = rotation; }

        glm::mat4 GetTransform();
    private:
        glm::vec3 m_Translation;
        glm::vec3 m_Scale;
        glm::vec3 m_Rotation;
    };
}