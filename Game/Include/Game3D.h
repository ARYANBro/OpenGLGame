#pragma once

#include <Engine/Game.h>

namespace Engine
{
    class VertexArray;
    class UniformBuffer;
    class ShaderProgram;
    struct Vector2;
    class Texture;
}

class Game3D : public Engine::Game
{
public:
    Game3D() = default;
    ~Game3D() = default;

    virtual void OnBegin() override;
    virtual void OnUpdate(const class Engine::DeltaTime& deltaTime) override;
    virtual void OnEnd() override;

private:
    std::shared_ptr<Engine::UniformBuffer> m_UBO;
};
