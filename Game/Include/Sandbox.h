#pragma once

#include "Game3D.h"

class Sandbox : public Game3D
{
public:
    virtual void OnBegin() override;
    virtual void OnUpdate(const class Engine::DeltaTime& deltaTime) override;
    virtual void OnEnd() override;

    virtual void OnKeyDown(int key) override;
    virtual void OnKeyUp(int key) override;
    virtual void OnMouseMove(const glm::vec2& deltaMousePos) override;

private:
    Engine::Entity* m_Entity;
    Engine::Entity* m_Entity2;
    Engine::Entity* m_Entity3;
    float m_Scale = 1.0;
    float m_RotationX = 0.0f;
    float m_RotationY = 0.0f;
    float m_RotationZ = 0.0f;
    float m_LocationZ = 0.0f;
    float m_LocationX = 0.0f;
    float m_ElapsedSeconds = 0.0f;
};