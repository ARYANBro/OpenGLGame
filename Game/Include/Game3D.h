#pragma once

#include <Engine/Game.h>

#include <glm/glm.hpp>

namespace Engine
{
    class UniformBuffer;
    class CameraEntity;
}

class Game3D : public Engine::Game
{
public:
    Game3D() = default;
    ~Game3D() = default;

    virtual void OnBegin() override;
    virtual void OnUpdate(const class Engine::DeltaTime& deltaTime) override;
    virtual void OnEnd() override;

    virtual void OnKeyDown(int key) override;
    virtual void OnMouseMove(const glm::vec2& deltaMousePos);
    virtual void OnMouseDown(Engine::MouseButton button) override;
    virtual void OnMouseUp(Engine::MouseButton button) override;

private:
    std::shared_ptr<Engine::UniformBuffer> m_UBO;
    float m_ElapsedTime = 0.0f;
    bool m_RightMouseDown = false;
    Engine::CameraEntity* m_Camera;
};
