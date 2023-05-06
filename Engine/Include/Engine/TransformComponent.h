#pragma once

#include "Component.h"

#include "Math/Matrix4.h"
#include "Math/Vector.h"

namespace Engine
{
    class TransformComponent : public Component
    {
    public:
        TransformComponent(const class Entity& entity) noexcept
            : Component(entity) {}
            
        virtual ~TransformComponent() noexcept override = default;

        void SetTranslation(const Math::Vector3& translation) noexcept { m_Translation = translation; }
        void SetScale(const Math::Vector3& scale) noexcept { m_Scale = scale;}
        void SetRotation(const Math::Vector3& rotation) noexcept { m_Rotation = rotation; }

        Math::Matrix4 GetTransform()
        {
            Math::Matrix4 translation;
            translation.SetTranslation(m_Translation);

            Math::Matrix4 scale;
            scale.SetScale(m_Scale);

            Math::Matrix4 rotation;
            scale.SetRotation(m_Rotation);

            return scale * rotation * translation;
        }

    private:
        Math::Vector3 m_Translation, m_Scale, m_Rotation;
    };
}