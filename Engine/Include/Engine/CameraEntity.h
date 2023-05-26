#pragma once

#include "Entity.h"

namespace Engine
{
    enum class ProjectionType
    {
        Prespective,
        Orthographic
    };

    class CameraEntity : public Entity
    {
    public:
        CameraEntity(World* world) noexcept
            : Entity(world) {}
        
        virtual ~CameraEntity() noexcept override = default;

        virtual void OnUpdate(const DeltaTime& deltaTime) override;

        void AddPosition(const glm::vec3& position) noexcept { m_Position += position; }
        void AddYaw(float yaw) noexcept { m_Yaw += yaw; }
        void AddPitch(float pitch) noexcept { m_Pitch += pitch; }

        void SetProjectionType(ProjectionType type) noexcept { m_ProjectionType = type; }
        void SetPosition(const glm::vec3& position) noexcept { m_Position = position; }
        void SetSpeed(float speed) noexcept { m_Speed = speed; }
        void SetYaw(float yaw) noexcept { m_Yaw = yaw; }
        void SetPitch(float pitch) noexcept { m_Pitch = pitch; }
        void SetSensitivity(float sensitivity) noexcept { m_Sensitivity = sensitivity; }
        void SetFOV(float fov) noexcept { m_FOV = fov; }
        void SetNear(float nearVal) noexcept { m_Near = nearVal; }
        void SetFar(float farVal) noexcept { m_Far = farVal; }

        glm::vec3 GetPosition() const noexcept { return m_Position; }
        glm::vec3 GetForward() const noexcept { return m_Forward; }
        glm::vec3 GetRight() const noexcept { return m_Right; }
        glm::vec3 GetUp() const noexcept { return m_Up; }
        float GetSpeed() const noexcept { return m_Speed; }
        float GetYaw() const noexcept { return m_Yaw; }
        float GetPitch() const noexcept { return m_Pitch; }
        float GetSensitivity() const noexcept { return m_Sensitivity; }
        float GetFOV() const noexcept { return m_FOV; }
        float GetNear() const noexcept { return m_Near; }
        float GetFar() const noexcept { return m_Far; }
        const glm::mat4& GetProjection() const noexcept { return m_Projection; }
        const glm::mat4& GetView() const noexcept { return m_View; }
    private:
        // Transform matricies;
        glm::mat4 m_Projection;
        glm::mat4 m_View;

        // Directional vectors
        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::vec3 m_Forward = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 m_Right;
        glm::vec3 m_Up;

        // Movment and view parameters
        ProjectionType m_ProjectionType = ProjectionType::Prespective;
        float m_Speed = 2.0f;
        float m_Yaw = 90.0f;
        float m_Pitch = 0.0f;
        float m_Sensitivity = 0.1f;
        float m_FOV = 90.0f;
        float m_Near = 0.1f;
        float m_Far = 1000.0f;
    };
}